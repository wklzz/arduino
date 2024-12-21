#include <Arduino.h>
#include "gpioControl.h"

GpioControl gpio(D1);

void setup() {
  Serial1.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  uint8_t data[] = {0xBB, 0xAA, 0x7E};
  for(int i = 0; i < 3; i++){
    Serial1.write(data[i]);
  }
}