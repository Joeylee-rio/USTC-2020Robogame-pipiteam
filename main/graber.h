#ifndef GRABER_H_
#define GRABER_H_
#include <Servo.h>
#include "linewalking1.h"

extern int Graber1, Graber2, Graber_front, Graber_back;
Servo servo1, servo2, servo3, servo4, servo5;
extern int pos1, pos2, pos3; //需要设为全局变量吗？
extern int rate_adjust1, rate;
void servo_init() {
  servo1.attach(6);
  servo2.attach(7);
  servo3.attach(8);
  servo4.attach(9);
  servo5.attach(10);
  pinMode(28, OUTPUT); //推杆
  pinMode(29, OUTPUT);

  servo1.write(0);//初始化舵机位置
  servo2.write(180);
  servo3.write(0);
  servo4.write(180);
  servo5.write(150);
  digitalWrite(28, HIGH);
  digitalWrite(29, LOW);
  delay(1000);
  digitalWrite(28, LOW); //停止会不会往下掉
  digitalWrite(29, LOW);

}

void Pusher(int state) {
  if (state) {
    digitalWrite(28, HIGH);
    digitalWrite(29, LOW);
  }
  else {
    digitalWrite(28, LOW);
    digitalWrite(29, HIGH);
  }
  delay(1500);
  digitalWrite(28, LOW);
  digitalWrite(29, LOW);
}

void Grab_up(int Graber_num) {
  switch (Graber_num) {
    case 1://待确定
      Pusher(0);
      flag_mask = 1; infrared_flag = 1;
      linewalking((3 + 12 + Direction_flag) % 4, 60, 30, NORFID, NOTIME,NOGRABER);
      flag_mask = 0; infrared_flag = 0;
      Pusher(1);
      for (; pos1 <= 50 ; pos1++) {
        servo4.write(180 - pos1);
        servo3.write(pos1);
        delay(10);
      }
      //Serial.println("@@@\n");
      linewalking((1 + 12 + Direction_flag) % 4, rate, rate_adjust, NORFID, TIME, NOGRABER); //Serial.println("@@@\n");
      break;

    case 2:
      Pusher(0);
      flag_mask = 1; infrared_flag = 1;
      linewalking((1 + 12 + Direction_flag) % 4, 60, 30, NORFID, NOTIME, NOGRABER);
      flag_mask = 0; infrared_flag = 0;
      Pusher(1);
      for (; pos2 <= 50 ; pos2++) {
        servo1.write(pos2);
        servo2.write(180 - pos2);
        delay(10);
      }
      linewalking((3 + 12 + Direction_flag) % 4, rate, rate_adjust, NORFID, TIME, NOGRABER);
      break;

    case 3:
      Pusher(1);
      flag_mask = 1; infrared_flag = 1;
      t = 1000;
      linewalking(0, 60, 30, NORFID, TIME, NOGRABER);
      t = 700;
       
      backward(100); delay(100);Stop();
      Stop();
      Pusher(0);
      for (; pos3 >=103 ; pos3--) {
        servo5.write(pos3);//舵机未转到指定位置会进行下一个语句吗
        delay(20);
      }
      
      flag_mask = 0; infrared_flag = 0;
      Pusher(1);
      break;

    default:;
  }
}

void Grab_down(int Graber_num) {
  switch (Graber_num) {
    case 1://待确定
      for (; pos1 >= 0 ; pos1--) {
        servo4.write(180 - pos1);
        servo3.write(pos1);
        delay(10);
      }
      Pusher(0);
      //interrupt();
      t=1000;
      linewalking((1 + 12 + Direction_flag) % 4, rate, rate_adjust, NORFID, TIME, NOGRABER); //判断Direction_flag可能不太合适
      t=700;
      Pusher(1);
      break;

    case 2:
      for (; pos2 >= 0 ; pos2--) {
        servo1.write(pos2);
        servo2.write(180 - pos2);
        delay(10);
      }
      Pusher(0);
      //interrupt();
      t=1000;
      linewalking((3 + 12 + Direction_flag) % 4, rate, rate_adjust, NORFID, TIME, NOGRABER);
      t=700;
      Pusher(1);
      break;

    case 3:
      Pusher(0);
      //servo5.write(150);
      for(;pos3<=150 ;pos3++){
        for(;pos3<=150 ;pos3++){
        servo5.write(pos3);//舵机未转到指定位置会进行下一个语句吗
        delay(20);
        }
      }
      //Pusher(1);
      break;
    default:;
  }
}
#endif
