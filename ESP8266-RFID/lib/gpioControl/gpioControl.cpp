#include "GpioControl.h"
#include <Arduino.h>

GpioControl::GpioControl(int pin) : _pin(pin) {
    pinMode(_pin, OUTPUT);
}

void GpioControl::turnUp() {
    digitalWrite(_pin, HIGH);   
}

void GpioControl::turnDown() {
    digitalWrite(_pin, LOW);   
}
