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

void setClientIp(const IPAddress &ip) {
    ::ip = ip;
}

void sendControls(Controls controls) {
    if (!handleWifi()) {
        delay(1000);
        return;
    }

    Serial.println(F("sendControls()"));

    static Controls oldControls{};
    // if (controls.x == oldControls.x || controls.y == oldControls.y) {
    //     return;
    // }
    oldControls = controls;

    const float minX = 683;
    const float maxX = 2114;

    const float maxY = 2658;
    const float minY = 1418;

    if (isAccessPoint()) {
        Serial.println("broadcasting...");
        auto broadcastIp = IPAddress{255, 255, 255, 255};
        udp.beginPacket(broadcastIp, 8088); // Broadcast
    }
    else {
        udp.beginPacket(ip, 8088);
    }
    // udp.write((const uint8_t *)"xx\n", 3);
    udp.println((controls.x - minX) / (maxX - minX) * 2.f - 1.f);
    udp.println((controls.y - minY) / (maxY - minY) * 2.f - 1.f);
    udp.println(++packageId);
    delay(3); // Some hack I found online. Might work.
    udp.endPacket();

    // Serial.write("udp sent\n");
}
