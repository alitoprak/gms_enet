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
static size_t s_event_packet_reader_offset_list[GMS_ENET_MAX_EVENT_COUNT] = {0};
static size_t s_event_count = 0;

#define GMS_ENET_MAX_PACKET_COUNT 1024
static ENetPacket* s_packet_list[GMS_ENET_MAX_PACKET_COUNT] = {0};
static size_t s_packet_writer_offset_list[GMS_ENET_MAX_PACKET_COUNT] = {0};
static size_t s_packet_count = 0;

GMS_EXPORT double gms_enet_initialize() {
    return enet_initialize() == 0 ? GMS_TRUE : GMS_FALSE;
}

GMS_EXPORT double gms_enet_deinitialize() {
    enet_deinitialize();
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_address_create(char* host, double port) {
    ENetAddress* address = &s_address_list[s_address_count];
    enet_address_set_host(address, host);
    address->port = (uint16_t)port;
    return (double)s_address_count++;
}

GMS_EXPORT double gms_enet_host_create(double address_handle, double max_peers, double max_channels, double in_bandwidth, double out_bandwidth) {
    const ENetAddress* address = &s_address_list[(size_t)address_handle];
    ENetHost* host = enet_host_create(address, max_peers, max_channels, in_bandwidth, out_bandwidth);
    s_host_list[s_host_count] = host;
    return (double)s_host_count++;
}

GMS_EXPORT double gms_enet_host_destroy(double host_handle) {
    ENetHost* host = s_host_list[(size_t)host_handle];
    enet_host_destroy(host);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_host_connect(double host_handle, double address_handle, double max_channels) {
    ENetHost* host = s_host_list[(size_t)host_handle];
    const ENetAddress* address = &s_address_list[(size_t)address_handle];
    ENetPeer* peer = enet_host_connect(host, address, max_channels, 0);
    s_peer_list[s_peer_count] = peer;
    return (double)s_peer_count++;
}

GMS_EXPORT double gms_enet_peer_reset(double peer_handle) {
    ENetPeer* peer = s_peer_list[(size_t)peer_handle];
    enet_peer_reset(peer);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_event_create() {
    return (double)s_event_count++;
}

GMS_EXPORT double gms_enet_event_type_get(double event_handle) {
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    return (double)event->type;
}

GMS_EXPORT double gms_enet_host_service(double host_handle, double event_handle, double timeout) {
    ENetHost* host = s_host_list[(size_t)host_handle];
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    s_event_packet_reader_offset_list[(size_t)event_handle] = 0;
    return enet_host_service(host, event, (uint32_t)timeout) > 0 ? GMS_TRUE : GMS_FALSE;
}

GMS_EXPORT double gms_enet_event_packet_get_length(double event_handle) {
    ENetEvent* event = &s_event_list[(size_t)event_handle];;
    return (double)event->packet->dataLength;
}

GMS_EXPORT double gms_enet_event_packet_read_u8(double event_handle) {
    uint8_t value;
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    size_t* offset = &s_event_packet_reader_offset_list[(size_t)event_handle];
    size_t value_size = sizeof(value);
    memcpy(&value, event->packet->data + *offset, value_size);
    *offset += value_size;
    return (double)value;
}

GMS_EXPORT double gms_enet_event_packet_read_i8(double event_handle) {
    int8_t value;
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    size_t* offset = &s_event_packet_reader_offset_list[(size_t)event_handle];
    size_t value_size = sizeof(value);
    memcpy(&value, event->packet->data + *offset, value_size);
    *offset += value_size;
    return (double)value;
}

GMS_EXPORT double gms_enet_event_packet_read_u16(double event_handle) {
    uint16_t value;
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    size_t* offset = &s_event_packet_reader_offset_list[(size_t)event_handle];
    size_t value_size = sizeof(value);
    memcpy(&value, event->packet->data + *offset, value_size);
    *offset += value_size;
    return (double)value;
}

GMS_EXPORT double gms_enet_event_packet_read_i16(double event_handle) {
    int16_t value;
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    size_t* offset = &s_event_packet_reader_offset_list[(size_t)event_handle];
    size_t value_size = sizeof(value);
    memcpy(&value, event->packet->data + *offset, value_size);
    *offset += value_size;
    return (double)value;
}

GMS_EXPORT double gms_enet_event_packet_read_u32(double event_handle) {
    uint32_t value;
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    size_t* offset = &s_event_packet_reader_offset_list[(size_t)event_handle];
    size_t value_size = sizeof(value);
    memcpy(&value, event->packet->data + *offset, value_size);
    *offset += value_size;
    return (double)value;
}

GMS_EXPORT double gms_enet_event_packet_read_i32(double event_handle) {
    int32_t value;
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    size_t* offset = &s_event_packet_reader_offset_list[(size_t)event_handle];
    size_t value_size = sizeof(value);
    memcpy(&value, event->packet->data + *offset, value_size);
    *offset += value_size;
    return (double)value;
}

GMS_EXPORT double gms_enet_event_packet_read_float(double event_handle) {
    static_assert(sizeof(float) == 4, "sizeof(float) should be 4 bytes!");
    float value;
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    size_t* offset = &s_event_packet_reader_offset_list[(size_t)event_handle];
    size_t value_size = sizeof(value);
    memcpy(&value, event->packet->data + *offset, value_size);
    *offset += value_size;
    return (double)value;
}

GMS_EXPORT double gms_enet_event_packet_read_double(double event_handle) {
    static_assert(sizeof(double) == 8, "sizeof(double) should be 8 bytes!");
    double value;
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    size_t* offset = &s_event_packet_reader_offset_list[(size_t)event_handle];
    size_t value_size = sizeof(value);
    memcpy(&value, event->packet->data + *offset, value_size);
    *offset += value_size;
    return value;
}

GMS_EXPORT double gms_enet_event_packet_destroy(double event_handle) {
    ENetEvent* event = &s_event_list[(size_t)event_handle];
    enet_packet_destroy(event->packet);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_packet_create(double packet_length, double packet_flags) {
    s_packet_list[s_packet_count] = enet_packet_create(NULL, (size_t)packet_length, (uint32_t)packet_flags);
    s_packet_writer_offset_list[s_packet_count] = 0;
    return s_packet_count++;
}

GMS_EXPORT double gms_enet_packet_write_u8(double packet_handle, double value) {
    size_t* offset = &s_packet_writer_offset_list[(size_t)packet_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    uint8_t casted_value = (uint8_t)value;
    memcpy(packet->data + *offset, &casted_value, sizeof(casted_value));
    *offset += sizeof(casted_value);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_packet_write_i8(double packet_handle, double value) {
    size_t* offset = &s_packet_writer_offset_list[(size_t)packet_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    int8_t casted_value = (int8_t)value;
    memcpy(packet->data + *offset, &casted_value, sizeof(casted_value));
    *offset += sizeof(casted_value);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_packet_write_u16(double packet_handle, double value) {
    size_t* offset = &s_packet_writer_offset_list[(size_t)packet_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    uint16_t casted_value = (uint16_t)value;
    memcpy(packet->data + *offset, &casted_value, sizeof(casted_value));
    *offset += sizeof(casted_value);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_packet_write_i16(double packet_handle, double value) {
    size_t* offset = &s_packet_writer_offset_list[(size_t)packet_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    int16_t casted_value = (int16_t)value;
    memcpy(packet->data + *offset, &casted_value, sizeof(casted_value));
    *offset += sizeof(casted_value);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_packet_write_u32(double packet_handle, double value) {
    size_t* offset = &s_packet_writer_offset_list[(size_t)packet_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    uint32_t casted_value = (uint32_t)value;
    memcpy(packet->data + *offset, &casted_value, sizeof(casted_value));
    *offset += sizeof(casted_value);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_packet_write_i32(double packet_handle, double value) {
    size_t* offset = &s_packet_writer_offset_list[(size_t)packet_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    int32_t casted_value = (int32_t)value;
    memcpy(packet->data + *offset, &casted_value, sizeof(casted_value));
    *offset += sizeof(casted_value);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_packet_write_float(double packet_handle, double value) {
    size_t* offset = &s_packet_writer_offset_list[(size_t)packet_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    float casted_value = (float)value;
    memcpy(packet->data + *offset, &casted_value, sizeof(casted_value));
    *offset += sizeof(casted_value);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_packet_write_double(double packet_handle, double value) {
    size_t* offset = &s_packet_writer_offset_list[(size_t)packet_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    memcpy(packet->data + *offset, &value, sizeof(value));
    *offset += sizeof(value);
    return GMS_TRUE;
}

GMS_EXPORT double gms_enet_peer_send(double peer_handle, double packet_handle) {
    ENetPeer* peer = s_peer_list[(size_t)peer_handle];
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    return enet_peer_send(peer, 0, packet) == 0 ? GMS_TRUE : GMS_FALSE;
}

GMS_EXPORT double gms_enet_packet_destroy(double packet_handle) {
    ENetPacket* packet = s_packet_list[(size_t)packet_handle];
    enet_packet_destroy(packet);
    return GMS_TRUE;
}