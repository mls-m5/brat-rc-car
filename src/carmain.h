#pragma once

#include "led.h"
#include "rcudp.h"
#include <Arduino.h>

int SENSOR_PIN = 0; // center pin of the potentiometer

int RPWM_Output = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output = 6; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)

// const int TEST_LED_PIN = 11;

int port = 80;

void setup() {
    Serial.begin(9600);

    initUdp(false);
    initLed();

    pinMode(RPWM_Output, OUTPUT);
    pinMode(LPWM_Output, OUTPUT);

    // pinMode(TEST_LED_PIN, OUTPUT);
}

void loop() {
    int sensorValue = analogRead(SENSOR_PIN);

    // sensor value is in the range 0 to 1023
    // the lower half of it we use for reverse rotation; the upper half for
    // forward rotation reverse rotation
    int reversePWM = -(sensorValue - 511) / 2;
    analogWrite(LPWM_Output, 0);
    analogWrite(RPWM_Output, reversePWM);

    delay(1000);
    // digitalWrite(TEST_LED_PIN, 1);
    setLed(true);

    delay(1000);
    // digitalWrite(TEST_LED_PIN, 0);
    setLed(false);
}