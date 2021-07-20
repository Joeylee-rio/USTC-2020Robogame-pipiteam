
#include "Arduino.h"
#define TIME 1
#define NOTIME 0
#define RFID 1
#define NORFID 0
#define GRABER 1
#define NOGRABER 0
#define BLOCK_NO 0
#include "linewalking1.h"
#include "interrupt.h"
#include "myRFID.h"
#include "graber.h"



//巡线变量组
int rate = 95, rate1 = 75, rate_adjust = 38, rate_adjust1 = 30, t = 600, t1 = 300, t3 = 1000; //巡线速度,t用于中断巡线,t3用于夹面罩，t1用于停止判断的中断//rate = 88,rate1=75,rate_adjust=50
int Direction, Direction_flag = 2; //巡线方向D1，2，3，4对应场地的前右后左，即逆时针编号，Direction对应小车的前后左右,未旋转时两者重合，旋转后两者相差固定数值，Direction_flag用来标志是否发生旋转，1为未旋转，0为旋转了
int sensor_1[4] = {0, 0, 0, 0}, sensor_2[4] = {0, 0, 0, 0}, sensor_3[4] = {0, 0, 0, 0}, sensor_4[4] = {0, 0, 0, 0}, infrared_front[2] = {1, 1}; //顺时针编号
float motor_one, motor_two, motor_three; int motor_1, motor_2, motor_3;
int flag = 0, flag1 = 1, flag_TIME = 0, flag_TIME1 = 1, flag_RFID = 0, interrupt_flag = 0, flag_mask = 0, infrared_flag = 0, infrared_flag1 = 0, infrared_graber = 1, flag_back = 0; //巡线中使用的标志变量
int red = 0; //记录重症病人位置


//整合过程变量组
int Location = 0, Location_farthest = 0; //当前所在节点层变量   帮助确定路线 初始为0
int Patient[7] = {0}; //病人1~6状态变量，0为未检查，1为健康，2为轻微，3为严重，初始为0
//int Position[5]  = {1,1,1,1,1}; //方舱医院内2~4位置变量，1为有病人，0为空床位，初始为1
int Graber1 = 0, Graber2 = 0; //两个爪子的变量  是否带病人，1为已带，0为未带
int pos1 = 0, pos2 = 0, pos3 = 160;

//uint8_t data[4];
int c = 0;

#include "integration_right.h"
#include "integration_left.h"


void setup() {
  //初始化
  //Serial.begin(9600);
  wheels_init();
  sensors_init();
  servo_init();
  delay(100);
  //Location=4;red=0;Location_farthest=4;
  //transfer_red_right();
  /*
    for (; pos2 <= 50 ; pos2++) {
        servo1.write(pos2);
        servo2.write(180 - pos2);
        delay(10);
      }
      delay(1000);
    for (; pos2 >= 0 ; pos2--) {
        servo1.write(pos2);
        servo2.write(180 - pos2);
        delay(10);
      }

  */
  
    Direction_flag--;
    flag_back=1;
  linewalking_delay((1 + 12 + Direction_flag) % 4, 75, 30, NOTIME);
  flag_back=0;
  rotate1(0); Direction_flag--; if (Direction_flag < 0)Direction_flag += 4;
  flag_TIME1 = 0; interrupt1();
  //infrared_flag=1;
  linewalking(3, 75, 30, NORFID, NOTIME, NOGRABER);
  //infrared_flag=0;
  Grab_up(3);
  go_right(rate1); delay(t3); Stop(); //时间t待定
  Grab_down(3); Stop();
  /*
    t=800;
    linewalking(3,rate,rate_adjust, NORFID, TIME,NOGRABER);
    linewalking(3,90,20, RFID, NOTIME,NOGRABER);
    Grab_up(2);
  */
  /*
    Direction_flag--;
    flag_back=1;
    linewalking_delay((1 + 12 + Direction_flag) % 4, 70, 20, NOTIME);
    flag_back=0;
    rotate1(0); Direction_flag--; if (Direction_flag < 0)Direction_flag += 4;
    flag_TIME1 = 0; interrupt1();
    //infrared_flag=1;
    linewalking(3, 75, 30, NORFID, NOTIME, NOGRABER);
    //infrared_flag=0;
    Grab_up(3);
    go_right(rate1); delay(t3); Stop(); //时间t待定
    Grab_down(3); Stop();
    //backward(rate1); delay(t3);Stop();
  */
  linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
  Location = 0;//Serial.print(Location);Serial.print(Location_farthest);Serial.println("\n");
  linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER); Location++; Location_farthest = Location; //Serial.print(Location);Serial.print(Location_farthest);Serial.println("\n");
  if (sensor_2[1] || sensor_2[2]) { //左场
    find_yellow_left();
    transfer_yellow_left();
    transfer_red_left();
    mask_left();
  }
  else if (sensor_4[1] || sensor_4[2]) { //右场
    find_yellow_right();
    transfer_yellow_right();
    transfer_red_right();
    mask_right();
  }
  Stop();

  //go_right(rate1); delay(t3); Stop();
  /*
    for (; pos3 >= 100 ; pos3--) {
        servo5.write(pos3);//舵机未转到指定位置会进行下一个语句吗
        delay(20);
    }
    delay(2000);
    servo5.write(150);
    /*
    for (; pos2 <= 50 ; pos2++) {
        servo1.write(pos2);
        servo2.write(180 - pos2);
        delay(20);
      }
    linewalking(3,rate,rate_adjust,NORFID,TIME,NOGRABER);
    linewalking(3, 60, 20, NORFID, NOTIME,GRABER);Serial.println(infrared_graber);
    /*
    Pusher(0);
    Direction_flag=3;
    linewalking((3+12+Direction_flag)%4,rate1,rate_adjust1,NORFID,NOTIME,NOGRABER);
    rotate1(1);Direction_flag++;
    flag_TIME1=0;interrupt1();
    //infrared_flag=1;
    linewalking(1, 75,30,NORFID, NOTIME,NOGRABER);
    //infrared_flag=0;
    Grab_up(3);
    go_left(rate1); delay(t3);Stop(); //时间t待定
    Grab_down(3);
    backward(rate1); delay(t3);Stop();
  */



  //linewalking(3, 75,30,NORFID, NOTIME,NOGRABER);delay(2000);
  /*
    Pusher(0);
    for(;pos3>=99 ;pos3--){
      servo5.write(pos3);//舵机未转到指定位置会进行下一个语句吗
      delay(20);
    }
    Pusher(1);
    delay(1000);
    servo5.write(150);
  */
  //linewalking(1,rate,rate_adjust,NORFID,NOTIME,NOGRABER);
}


void loop() {
  /*
    sensor_read(3);      //可以考虑读到RFID停止        左边进入横向黑线正中 右边进入横向黑线正中
    Serial.println("&&&");
    Serial.print(infrared_front[0]);Serial.print(infrared_front[1]);


    //Serial.print(digitalRead(infrared_graber_2));
    /*
    linewalking(1,rate,rate_adjust,NORFID,TIME,NOGRABER);
    linewalking(1, 60, 20, NORFID, NOTIME,NOGRABER);
    linewalking(3,rate,rate_adjust,NORFID,TIME,NOGRABER);
    linewalking(3,rate,rate_adjust,NORFID,NOTIME,NOGRABER);
    linewalking(3,rate,rate_adjust,NORFID,TIME,NOGRABER);
    linewalking(3, 60, 20, NORFID, NOTIME,NOGRABER);
    linewalking(1,rate,rate_adjust,NORFID,TIME,NOGRABER);
    linewalking(1,rate,rate_adjust,NORFID,NOTIME,NOGRABER);
    /*
    flag_mask=1;
    forward(58);delay(2000);
    backward(58);delay(2000);

    /*
    linewalking(0, rate,rate_adjust,NORFID, NOTIME,NOGRABER);delay(100);
    linewalking(0, rate,rate_adjust,NORFID, NOTIME,NOGRABER);delay(100);
    linewalking(0, rate,rate_adjust,NORFID, NOTIME,NOGRABER);delay(100);
    linewalking(2, rate,rate_adjust,NORFID, NOTIME,NOGRABER);delay(100);
    linewalking(2, rate,rate_adjust,NORFID, NOTIME,NOGRABER);delay(100);
    linewalking(2, rate,rate_adjust,NORFID, NOTIME,NOGRABER);delay(100);

    /*
    sensor_read(1);
    //Serial.print(sensor_4[0]);Serial.print(sensor_4[1]);Serial.print(sensor_4[2]);Serial.println(sensor_4[3]);
    Serial.println(sensor_3[3]);

    /*
    flag_mask=1;
    forward(rate1);delay(2000);Stop();
    backward(rate1);delay(2000);Stop();


    /*
    rotate(1);Direction_flag++;delay(200);
    rotate(1);Direction_flag++;delay(200);
    rotate(0);Direction_flag--;delay(200);
    rotate(0);Direction_flag--;delay(200);
  */
}
