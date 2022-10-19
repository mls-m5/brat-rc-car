/*
IBT-2 Motor Control Board driven by Arduino.

Speed and direction controlled by a potentiometer attached to analog input 0.
One side pin of the potentiometer (either one) to ground; the other side pin to
+5V

Connection to the IBT-2 board:
IBT-2 pin 1 (RPWM) to Arduino pin 5(PWM)
IBT-2 pin 2 (LPWM) to Arduino pin 6(PWM)
IBT-2 pins 3 (R_EN), 4 (L_EN), 7 (VCC) to Arduino 5V pin
IBT-2 pin 8 (GND) to Arduino GND
IBT-2 pins 5 (R_IS) and 6 (L_IS) not connected
*/

#include <Arduino.h>

#include "led.h"
#include "rcudp.h"
#include <pins_arduino.h>

int SENSOR_PIN = 0; // center pin of the potentiometer

int RPWM_Output = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output = 6; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)

auto LED_BUILTIN = 2;

void setup() {
    // pinMode(RPWM_Output, OUTPUT);
    // pinMode(LPWM_Output, OUTPUT);

    // pinMode(LED_BUILTIN, OUTPUT);

    // pinMode(14, OUTPUT);
    // digitalWrite(14, 0);

    Serial.begin(9600);

    pinMode(32, ANALOG);

    initLed();
    initUdp();

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

    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);

    auto controls = Controls{};

    controls.x = a; // Ordinary initialization does not seem to work
    controls.y = b;
    sendControls(controls);

    delay(40);
}
