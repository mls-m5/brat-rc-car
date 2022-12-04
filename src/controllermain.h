#pragma once

#include "led.h"
#include "rcudp.h"
#include <Arduino.h>

void setup() {

    Serial.begin(9600);

    pinMode(32, ANALOG);

    initLed();
    initUdp(true);

    flashLed();

    Serial.setDebugOutput(true);
}

void loop() {
    // int sensorValue = analogRead(SENSOR_PIN);

    // sensor value is in the range 0 to 1023
    // the lower half of it we use for reverse rotation; the upper half for
    // forward rotation reverse rotation
    // int reversePWM = -(sensorValue - 511) / 2;
    // analogWrite(LPWM_Output, 0);
    // analogWrite(RPWM_Output, reversePWM);

    int a = analogRead(32);
    int b = analogRead(33);

    setLed(true);

    auto controls = Controls{};

    controls.x = a; // Ordinary initialization does not seem to work
    controls.y = b;
    sendControls(controls);

    delay(40);
}
