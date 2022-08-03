#include <Arduino.h>
#include <WiFi.h>

auto diode = 2;

void setup()
{
  pinMode(diode, OUTPUT);
}

void loop()
{
  digitalWrite(diode, LOW);
  delay(100);
  digitalWrite(diode, HIGH);

  delay(100);
}