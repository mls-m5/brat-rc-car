
#include "led.h"
#include <Arduino.h>

namespace {
constexpr int LED_PIN = 2;
}

void initLed() {
    pinMode(LED_PIN, OUTPUT);
}

void setLed(bool value) {
    digitalWrite(LED_PIN, value? HIGH: LOW);
}