#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H

class GpioControl {
public:
  GpioControl(int pin);
  void turnUp();
  void turnDown();
private:
  int _pin;
};

#endif