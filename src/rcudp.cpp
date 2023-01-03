#include "rcudp.h"
#include "rcwifi.h"
#include <Arduino.h>
#include <WiFiUdp.h>
#include <algorithm>
#include <array>

namespace {

WiFiUDP udp;

auto packageId = (unsigned long){0};

auto ip = IPAddress{};
// auto ip = IPAddress{WIFI_IP_ADDR};

} // namespace

void initUdp(bool isAp, bool isCar) {
    initWifi(isAp);
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

    // Serial.println(F("sendControls()"));

    static Controls oldControls{};
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

bool readUdp(Controls &controls) {
    auto data = std::array<char, 30>{};

    auto packetSize = udp.parsePacket();
    if (!packetSize) {
        return false;
    }
    auto len = udp.read(data.data(), data.size() - 1);
    if (!len) {
        return false;
    }
    // data.at(len) = 0;
    // Serial.println(data.data());

    auto f1 = std::find(data.begin(), data.end(), '\n');
    if (f1 == data.end()) {
        return false;
    }
    auto f2 = std::find(f1 + 1, data.end(), '\n');
    if (f2 == data.end()) {
        return false;
    }

    controls.x = String(data.data(), f1 - data.begin()).toFloat();
    controls.y = String(f1, (f2 - f1)).toFloat();

    return true;
}
