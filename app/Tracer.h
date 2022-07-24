#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include "util.h"        // <3>
#include "Clock.h"
#include "SonarSensor.h"

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
  SonarSensor sonarSensor;
  int8_t mThreshold = 20;  // <4>
  int8_t flg=0;// 0=通常 1=難所
  int8_t high=0;
  int8_t low=0;

  int8_t pre_distance=0;
  int8_t count=0;
/*#ifndef MAKE_RASPIKE
  int8_t pwm = (Motor::PWM_MAX) / 6;
#else
  int8_t pwm = 60;
#endif*/
};
