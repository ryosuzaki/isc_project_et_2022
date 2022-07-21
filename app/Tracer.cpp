#include "Tracer.h" // <1>
Tracer::Tracer():
  leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2) ,sonarSensor(PORT_3){ // <2>
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
  high=50;
  low=20;
  mThreshold=20;

  //flg 0=通常 1以降=難所
  if(flg==0){
    printf("輝度：%d　カラーナンバー：%d　環境光の強さ：%d\n" , colorSensor.getBrightness(),colorSensor.getColorNumber(),colorSensor.getAmbient());
    //難所探知機能 緑を検出したらflgを1に変更
    if(colorSensor.getColorNumber()==3){
      leftWheel.setPWM(-30);
      rightWheel.setPWM(-30);
      flg=1;
    }

    //****************************
    //ここに通常ルートのコードを書く
    if(colorSensor.getBrightness() >= mThreshold) { // <1>
      leftWheel.setPWM(high);
      rightWheel.setPWM(low);
    }else {   // <2>
      leftWheel.setPWM(low);
      rightWheel.setPWM(high);
    }
    //ここまで通常ルートのコードを書く
    //******************************

  }else if(flg==1){
    //
    leftWheel.setPWM(0);
    rightWheel.setPWM(20);
    if (sonarSensor.getDistance()<100){
      flg=2;
      pre_distance=sonarSensor.getDistance();
    }
  }else if(flg==2){
    //方向転換
    rightWheel.setPWM(-5);
    if (pre_distance<sonarSensor.getDistance()){
      flg=3;
    }
    pre_distance=sonarSensor.getDistance();
    printf("%d\n",sonarSensor.getDistance());
  }else if(flg==3){
    //ブロック位置合わせ
    count+=1;
    rightWheel.setPWM(3);
    if(count==6){
      flg=4;
    }
    printf("%d\n",count);
  }else if(flg==4){
    //高得点位置まで移動
    leftWheel.setPWM(30);
    rightWheel.setPWM(30);
    if(sonarSensor.getDistance()<18){
      leftWheel.setPWM(0);
      rightWheel.setPWM(0);
      flg=5;
    }
    printf("%d\n",sonarSensor.getDistance());
  }
  
}
