
#include "rcwifi.h"
#include "led.h"
#include "rcudp.h"
#include <Arduino.h>
#include <WiFi.h>

namespace {

bool isAP = true;

void startWifiClient() {

    Serial.printf("connecting to %s ", WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.hostname("rchost");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        setLed(true);
        delay(50);
        setLed(false);
        Serial.print(".");
    }

    flashLed(10, 50);

    Serial.println(F("WiFi connected"));
    Serial.println(F("IP address: "));
    Serial.println(WiFi.localIP());
}

void startWifiAP() {
    Serial.println(F("starting AP"));

    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(gateway, gateway, subnet);
    WiFi.softAP("rc-controller", "controller");
    Serial.println(F("AP started"));
}

} // namespace

void initWifi(bool isAP) {
    ::isAP = isAP;

    if (::isAP) {
        startWifiAP();

        return;
    }

    startWifiClient();
}

bool handleWifi() {
    if (!::isAP) {
        return true;
    }

    auto num = WiFi.softAPgetStationNum();

    Serial.println(F("handle wifi"));

    if (!num) {
        Serial.println("no clients connected");
        return false;
    }

    return true;
}

bool isAccessPoint() {
    return ::isAccessPoint;
}