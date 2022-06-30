
#include "Tracer.h" // <1>
Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2) { // <2>
  }

void Tracer::init() {
  init_f("Tracer");
}

void Tracer::terminate() {
  msg_f("Stopped.", 1);
  leftWheel.stop();  // <1>
  rightWheel.stop();
}

void Tracer::run() {
  msg_f("running...", 1);
  pwm1=80;
  pwm2=50;
  mThreshold = 20;
  if(colorSensor.getBrightness() >= mThreshold) { // <1>
    leftWheel.setPWM(50);
    rightWheel.setPWM(20);
  } else {   // <2>
    leftWheel.setPWM(20);
    rightWheel.setPWM(50);
  }
}
