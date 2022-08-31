#include "rcudp.h"
#include "rcwifi.h"
#include <Arduino.h>
#include <AsyncUDP.h>
#include <WiFiUdp.h>

namespace {

WiFiUDP udp;

auto packageId = (unsigned long){0};

auto ip = IPAddress{WIFI_IP_ADDR};

} // namespace

void initUdp() {
    initWifi();
    udp.begin(8088);
}

void sendControls(Controls controls) {
    udp.beginPacket(ip, 8088);
    udp.write((const uint8_t *)"xx\n", 3);
    udp.endPacket();

    Serial.write("udp sent\n");
}
