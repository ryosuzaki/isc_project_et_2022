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
  high=60;
  low=30;
  mThreshold=20;
  printf("輝度：%d　カラーナンバー：%d　環境光の強さ：%d\n" , colorSensor.getBrightness(),colorSensor.getColorNumber(),colorSensor.getAmbient());
  //printf("RGB Raw値：%d" , colorSensor.getRawColor());
  if(colorSensor.getBrightness() >= mThreshold) { // <1>
    leftWheel.setPWM(high);
    rightWheel.setPWM(low);
  } else {   // <2>
    leftWheel.setPWM(low);
    rightWheel.setPWM(high);
  }
}
