
#include "led.h"
#include <Arduino.h>

namespace {
constexpr int LED_PIN = 2;
}

void initLed() {
    pinMode(LED_PIN, OUTPUT);
}

void setLed(bool value) {
    digitalWrite(LED_PIN, value ? HIGH : LOW);
}

void flashLed(int num, int ms) {
    for (int i = 0; i < num; ++i) {
        setLed(true);
        delay(ms);
        setLed(false);
        delay(ms);
    }
}