#pragma once

#include "led.h"
#include "rcudp.h"
#include <Arduino.h>

// int RPWM_Output = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 1
// (RPWM) int LPWM_Output = 6; // Arduino PWM output pin 6; connect to IBT-2 pin
// 2 (LPWM)
int R_EN = 26;
int L_EN = 27;

// const int TEST_LED_PIN = 11;

// Test
const int freq = 5000;    // frequency in Hz
const int RChannel = 0;   // channel, from 0 to 15
const int LChannel = 1;   // channel, from 0 to 15
const int resolution = 8; // resolution, from 1 to 16
const int RPWN = 12;      // GPIO pin
const int LPWN = 14;      // GPIO pin
int port = 80;

void setup() {
    Serial.begin(9600);

    initUdp(false, false);
    initLed();

    // pinMode(RPWM_Output, OUTPUT);
    // pinMode(LPWM_Output, OUTPUT);
    pinMode(R_EN, OUTPUT);
    pinMode(L_EN, OUTPUT);
    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, HIGH);

    /// Test:

    // configure LED PWM functionalitites
    ledcSetup(RChannel, freq, resolution);
    ledcSetup(LChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(RPWN, RChannel);
    ledcAttachPin(LPWN, LChannel);
}

void loop() {
    // Serial.println("test");
    auto controls = Controls{};
    while (readUdp(controls)) {
        controls.normalize();
        if (controls.y > 0) {
            // delay(15);
            ledcWrite(RChannel, controls.y * 255);
            ledcWrite(LChannel, 0);
        }
        else {
            ledcWrite(LChannel, -controls.y * 255);
            ledcWrite(RChannel, 0);
        }
    }
}