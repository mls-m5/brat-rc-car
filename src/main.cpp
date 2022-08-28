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
#ifdef IS_CONTROLLER
#include <ESP8266WiFi.h>
#elif IS_CAR

#endif
#include <WiFiUdp.h>

int SENSOR_PIN = 0; // center pin of the potentiometer

int RPWM_Output = 5; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
int LPWM_Output = 6; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)

const int TEST_LED_PIN = 11;

int port = 80;

WiFiUDP udp;

void setup() {

    pinMode(RPWM_Output, OUTPUT);
    pinMode(LPWM_Output, OUTPUT);

    pinMode(TEST_LED_PIN, OUTPUT);

    udp.begin(80);
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
    digitalWrite(TEST_LED_PIN, 1);

    delay(1000);
    digitalWrite(TEST_LED_PIN, 0);

    udp.beginPacket(udp.remoteIP(), 80);
    udp.write(10); // test;
    udp.endPacket();
}