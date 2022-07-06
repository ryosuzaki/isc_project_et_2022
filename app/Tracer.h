#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>

using namespace ev3api;  // <4>

class Tracer {  // <1>
public:
  Tracer();
  void run();       // <2>
  void init();
  void terminate();

private:
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor; // <3>
  int8_t mThreshold = 20;  // <4>
  int8_t high=60;
  int8_t low=30;
/*#ifndef MAKE_RASPIKE
  int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  int8_t pwm = 60;
#endif*/
};
