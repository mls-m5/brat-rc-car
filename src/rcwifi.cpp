
#include "rcwifi.h"
#include "led.h"
#include <Arduino.h>
#include <WiFi.h>

void initWifi() {
    // if (!enabled) {
    //     return;
    // }

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

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}