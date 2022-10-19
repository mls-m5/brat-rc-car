
#include "led.h"
#include <Arduino.h>

namespace {
constexpr int LED_PIN = 2;
}

void initLed() {
    pinMode(LED_PIN, OUTPUT);
    // const auto freq = 500;
    // const auto resolution = 8;
    // ledcSetup(LED_PIN, freq, resolution);
    // ledcAttachPin(LED_PIN, 0);
}

void setLed(bool value) {
    // digitalWrite(LED_PIN, value ? HIGH : LOW);
    // ledcWrite(0, value * 50);
    analogWrite(LED_PIN, 50 * value);
}

void flashLed(int num, int ms) {
    for (int i = 0; i < num; ++i) {
        setLed(false);
        delay(ms);
        setLed(true);
        delay(ms);
    }
}