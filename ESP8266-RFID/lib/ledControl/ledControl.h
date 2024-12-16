#ifndef LEDCONTROL_H
#define LEDCONTROL_H

class LedControl {
public:
  LedControl(int pin);
  void turnOn();
  void turnOff();
private:
  int _pin;
};

#endif