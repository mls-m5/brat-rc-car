#include <Arduino.h>
#include <thread>

void pinMode(int pin, int value) {}

int analogRead(int pin) {
    return 0;
}

void analogWrite(int pin, int value) {}

void delay(int value) {
    using namespace std::literals;
    std::this_thread::sleep_for(value * 1ms);
}

void digitalWrite(int pin, int value) {}

int main(int argc, char *argv[]) {

    return 0;
}
