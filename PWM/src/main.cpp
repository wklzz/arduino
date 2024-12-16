#include <Arduino.h>
#include <ESP32_PWM.h>

ESP32_PWM pwm;

void setup() {
  Serial.begin(115200);
  
  pwm.init();  
  Serial.println("Ready");
  pwm.setPWM(GPIO_NUM_18, 50, 8);
  pwm.run();
}

void loop() {
  // put your main code here, to run repeatedly:
}
