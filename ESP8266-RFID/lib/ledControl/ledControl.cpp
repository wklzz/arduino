#include "LedControl.h"
#include <Arduino.h>

LedControl::LedControl(int pin) : _pin(pin) {
  pinMode(_pin, OUTPUT);
}

void LedControl::turnOn() {
  Serial.println("LED ON");
  digitalWrite(_pin, HIGH);
}

void LedControl::turnOff() {
  Serial.println("LED OFF");
  digitalWrite(_pin, LOW);
}