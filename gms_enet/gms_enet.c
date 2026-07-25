#include <enet/enet.h>
#include <stdint.h>
#include <string.h>

#ifdef _WIN32
    #define GMS_EXPORT __declspec(dllexport)
#else
    #define GMS_EXPORT
#endif

#define GMS_TRUE 1.0
#define GMS_FALSE 0.0

#define GMS_INVALID_HANDLE -1.0

#define GMS_ENET_MAX_ADDRESS_COUNT 1024
static ENetAddress s_address_list[GMS_ENET_MAX_ADDRESS_COUNT] = {0};
static size_t s_address_count = 0;

#define GMS_ENET_MAX_HOST_COUNT 1024
static ENetHost* s_host_list[GMS_ENET_MAX_HOST_COUNT] = {0};
static size_t s_host_count = 0;

#define GMS_ENET_MAX_PEER_COUNT 1024
static ENetPeer* s_peer_list[GMS_ENET_MAX_PEER_COUNT] = {0};
static size_t s_peer_count = 0;

#define GMS_ENET_MAX_EVENT_COUNT 1024
static ENetEvent s_event_list[GMS_ENET_MAX_EVENT_COUNT] = {0};
static size_t s_event_count = 0;

GMS_EXPORT double gms_enet_initialize() {
    return enet_initialize() == 0 ? GMS_TRUE : GMS_FALSE;
}

GMS_EXPORT double gms_enet_deinitialize() {
    enet_deinitialize();
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_address_create(char* host, double port) {
    if (s_address_count >= GMS_ENET_MAX_ADDRESS_COUNT) {
        return GMS_INVALID_HANDLE;
    }

    if (enet_address_set_host(&s_address_list[s_address_count], host) != 0) {
        return GMS_INVALID_HANDLE;
    }

    if (port < 0.0 || port > UINT16_MAX) {
        return GMS_INVALID_HANDLE;
    }
    s_address_list[s_address_count].port = (uint16_t)port;

    return (double)s_address_count++;
}

static ENetAddress* _get_address(double address_handle) {
    if (address_handle < 0.0 || address_handle >= s_address_count) {
        return NULL;
    }

    return &s_address_list[(size_t)address_handle];
}

GMS_EXPORT double gms_enet_host_create(double address_handle, double max_peers, double max_channels, double in_bandwidth, double out_bandwidth) {
    if (s_host_count >= GMS_ENET_MAX_HOST_COUNT) {
        return GMS_INVALID_HANDLE;
    }
    
    const ENetAddress* address = _get_address(address_handle);
    ENetHost* host = enet_host_create(address, max_peers, max_channels, in_bandwidth, out_bandwidth);
    if (host == NULL) {
        return GMS_INVALID_HANDLE;
    }
    s_host_list[s_host_count] = host;
    
    return (double)s_host_count++;
}

static ENetHost* _get_host(double host_handle) {
    if (host_handle < 0.0 || host_handle >= s_host_count) {
        return NULL;
    }

    return s_host_list[(size_t)host_handle];
}

GMS_EXPORT double gms_enet_host_destroy(double host_handle) {
    ENetHost* host = _get_host(host_handle);
    if (host == NULL) {
        return GMS_FALSE;
    }

    enet_host_destroy(host);

    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_host_connect(double host_handle, double address_handle, double max_channels) {
    if (s_peer_count >= GMS_ENET_MAX_PEER_COUNT) {
        return GMS_INVALID_HANDLE;
    }
    
    ENetHost* host = _get_host(host_handle);
    if (host == NULL) {
        return GMS_INVALID_HANDLE;
    }

    const ENetAddress* address = _get_address(address_handle);
    if (address == NULL) {
        return GMS_INVALID_HANDLE;
    }

    ENetPeer* peer = enet_host_connect(host, address, max_channels, 0);
    if (peer == NULL) {
        return GMS_INVALID_HANDLE;
    }
    s_peer_list[s_peer_count] = peer;

    return (double)s_peer_count++;
}

static ENetPeer* _get_peer(double peer_handle) {
    if (peer_handle < 0.0 || peer_handle > s_peer_count) {
        return NULL;
    }

    return s_peer_list[(size_t)peer_handle];
}

GMS_EXPORT double gms_enet_peer_reset(double peer_handle) {
    ENetPeer* peer = _get_peer(peer_handle);
    if (peer == NULL) {
        return GMS_FALSE;
    }

    enet_peer_reset(peer);

    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_event_create() {
    if (s_event_count >= GMS_ENET_MAX_EVENT_COUNT) {
        return GMS_INVALID_HANDLE;
    }

    return (double)s_event_count++;
}

static ENetEvent* _get_event(double event_handle) {
    if (event_handle < 0.0 || event_handle >= s_event_count) {
        return NULL;
    }

    return &s_event_list[(size_t)event_handle];
}

GMS_EXPORT double gms_enet_event_get_type(double event_handle) {
    ENetEvent* event = _get_event(event_handle);
    if (event == NULL) {
        return GMS_INVALID_HANDLE;
    }

    return (double)event->type;
}

GMS_EXPORT double gms_enet_host_service(double host_handle, double event_handle, double timeout) {
    ENetHost* host = _get_host(host_handle);
    if (host == NULL) {
        return GMS_FALSE;
    }

    ENetEvent* event = _get_event(event_handle);
    if (event == NULL) {
        return GMS_FALSE;
    }

    if (timeout < 0.0 || timeout > UINT32_MAX) {
        return GMS_FALSE;
    }

    if (enet_host_service(host, event, (uint32_t)timeout) > 0) {
        return GMS_TRUE;
    }

    return GMS_FALSE;
}

GMS_EXPORT double gms_enet_event_get_packet_length(double event_handle) {
    ENetEvent* event = _get_event(event_handle);
    if (event == NULL) {
        return 0.0;
    }

    return event->packet->dataLength;
}

static uint8_t* _buffer_from_str(char* buffer_address_str) {
    unsigned long long buffer_address = strtoull(buffer_address_str, NULL, 16);
    return (uint8_t*)buffer_address;
}

GMS_EXPORT double gms_enet_event_get_packet(double event_handle, char* buffer_address_str) {
    ENetEvent* event = _get_event(event_handle);
    if (event == NULL) {
        return GMS_FALSE;
    }

    uint8_t* buffer = _buffer_from_str(buffer_address_str);
    if (buffer == NULL) {
        return GMS_FALSE;
    }

    memcpy(buffer, event->packet->data, event->packet->dataLength);
    return GMS_TRUE;
}