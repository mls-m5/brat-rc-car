#pragma once

#include "led.h"
#include "rcudp.h"
#include <Arduino.h>

struct PCMData {
    int pin;        // GPIO the servo is attached to
    int channel;    // LEDC channel number
    int freq;       // Servo frequency (50Hz)
    int resolution; // Bits of resolution (up to 16 for ESP32)
    int minValue;   // Corresponds to 1ms pulse width
    int maxValue;   // Corresponds to 2ms pulse width
    int pulseWidth; // Current pulse width

    void setup() {
        ledcSetup(channel, freq, resolution);
        ledcAttachPin(pin, channel);
    }

    void write() {
        ledcWrite(channel, pulseWidth);
    }

    void pulseWidthSet(float x) {
        pulseWidth = (x + 1) / 2 * (maxValue - minValue) + minValue;
    }
};

// 50Hz frequency corresponds to 20ms period
// 16 bit resolution corresponds to a range from 0 to 65535 (2^16 - 1)
// 1ms pulse width corresponds to 1/20 of the total range
// 2ms pulse width corresponds to 2/20 of the total range

const int servoBitResolution = 12;

PCMData servo = {
    .pin = 25,
    .channel = 2,
    .freq = 50,
    .resolution = servoBitResolution,
    .minValue = ((1 << servoBitResolution) - 1) * 1 / 2 /
                20, // Update minValue and maxValue to match new resolution
    .maxValue = ((1 << servoBitResolution) - 1) * 5 / 2 / 20,
    .pulseWidth = 0,
};

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
// int port = 80;

void setup() {
    Serial.begin(9600);

    initUdp(false, false);
    initLed();

    pinMode(R_EN, OUTPUT);
    pinMode(L_EN, OUTPUT);
    digitalWrite(R_EN, HIGH);
    digitalWrite(L_EN, HIGH);

    // configure LED PWM functionalitites
    ledcSetup(RChannel, freq, resolution);
    ledcSetup(LChannel, freq, resolution);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(RPWN, RChannel);
    ledcAttachPin(LPWN, LChannel);

    servo.setup();
}

void loop() {
    // Serial.println("test");
    auto controls = Controls{};

    static float lastX = 0;
    while (readUdp(controls)) {
        lastX = controls.x;
        controls.normalize();

        servo.pulseWidthSet(controls.x * .5);
        servo.write();
        Serial.println(controls.x);

        if (controls.y > 0) {
            // delay(15);
            ledcWrite(LChannel, 0);
            ledcWrite(RChannel, controls.y * 255);
        }
        else {
            ledcWrite(RChannel, 0);
            ledcWrite(LChannel, -controls.y * 255);
        }
    }
}