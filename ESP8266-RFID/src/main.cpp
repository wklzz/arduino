#include <Arduino.h>
#include "gpioControl.h"

GpioControl gpio(D1);

void setup() {
  Serial.begin(921600);
}

void loop() {
  // put your main code here, to run repeatedly:
  gpio.turnUp();
  Serial.write("Up\n");
}