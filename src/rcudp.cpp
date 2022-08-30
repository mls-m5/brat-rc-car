#include "rcudp.h"
#include <Arduino.h>
#include <WiFiUdp.h>


namespace {

WiFiUDP udp;

auto packageId = (unsigned long){0};

auto ip = IPAddress{192, 168, 0, 100};

} // namespace

void initUdp() {
    udp.begin(8088);
}

void sendControls(Controls controls) {
    udp.beginPacket(ip, 8088);
    udp.write((const uint8_t*)"xxx", 3);
    udp.endPacket();
}
