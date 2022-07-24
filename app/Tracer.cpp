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
  //
  mThreshold=20;
  //
  brightness=colorSensor.getBrightness();
  color_number=colorSensor.getColorNumber();
  ambient=colorSensor.getAmbient();
  distance=sonarSensor.getDistance();
  printf("輝度：%d　カラーナンバー：%d　環境光の強さ：%d　距離：%d\n",brightness,color_number,ambient,distance);
  
  //state 0は通常 1以降は難所
  if(state==0){
    //****************************
    //ここに通常ルートのコードを書く
    if(brightness >= mThreshold) { // <1>
      leftWheel.setPWM(high);
      rightWheel.setPWM(low);
    }else {   // <2>
      leftWheel.setPWM(low);
      rightWheel.setPWM(high);
    }
    //ここまで通常ルートのコードを書く
    //******************************

    //青い線を通過したら、passed_blueを1に変更
    if(color_number==2){
      passed_blue=1;
      high=40;
      low=20;
      printf("青い線を通過\n");
    }
    
    //難所探知機能 緑を検出したらstateを1に変更
    if(color_number==3){
      leftWheel.setPWM(-30);
      rightWheel.setPWM(-30);
      state=1;
      printf("難所探知\n");
    }

  }else if(state==1){
    //左に回転
    leftWheel.setPWM(0);
    rightWheel.setPWM(20);
    if (distance<98){
      state=2;
      pre_distance=distance;
    }
    printf("state=1 左に回転:%d\n",distance);
  }else if(state==2){
    //方向転換
    rightWheel.setPWM(-5);
    if (pre_distance<distance){
      state=3;
    }
    pre_distance=distance;
    printf("state=2 右に回転:%d\n",distance);
  }else if(state==3){
    //ブロック位置合わせ
    if(count==6){
      state=4;
    }else{
      count+=1;
      rightWheel.setPWM(3);
      printf("state=3 ブロック位置合わせ回数:%d\n",count);
    }
  }else if(state==4){
    //高得点位置まで移動
    if(distance<20){
      leftWheel.setPWM(0);
      rightWheel.setPWM(0);
      printf("停止\n");
      state=5;
    }else{
      leftWheel.setPWM(30);
      rightWheel.setPWM(30);
      printf("state=4 壁までの距離:%d\n",distance);
    }
  }
}
