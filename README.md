> **Warning**  
> This extension is in an **experimental state** and may contain critical bugs. Use with caution in production environments. You can use [Issues](https://github.com/alitoprak/gms_enet/issues) to report bugs or suggest changes.

# GMS ENet
**GMS ENet** brings the power of the [ENet](https://github.com/lsalzman/enet) reliable UDP networking library to GameMaker Studio.

## Key Features
- **Fast & Reliable UDP:** Leverages ENet's custom reliability and packet sequencing layer, ideal for real-time, fast-paced multiplayer games.
- **Developer-Friendly:** Provides a simple GML interface to connect and communicate with dedicated servers.

## Limitations
- I currently can only test and target Windows (Linux and Android planned for near future).
- There is a small overhead compared to native usage of ENet.
- There are almost no safety checks in order to minimize overhead.

## Installation
- Either build the extension yourself or grab a `.yymps` package from [Releases](https://github.com/alitoprak/gms_enet/releases).
