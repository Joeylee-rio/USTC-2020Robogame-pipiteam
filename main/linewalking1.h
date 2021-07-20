#ifndef linewalking1_H_
#define linewalking1_H_
#include "Arduino.h"
#include "wheel.h"
#include "myRFID.h"
#include "interrupt.h"

#define sensor_front_1 46 //以下具体接口未定
#define sensor_front_2 47
#define sensor_front_3 48
#define sensor_front_4 49

#define sensor_back_1 36
#define sensor_back_2 37
#define sensor_back_3 38
#define sensor_back_4 39

#define sensor_left_1 50
#define sensor_left_2 51
#define sensor_left_3 52
#define sensor_left_4 53

#define sensor_right_1 32
#define sensor_right_2 33
#define sensor_right_3 34
#define sensor_right_4 35

#define infrared_1_1 42 //顺时针编号,待定
#define infrared_1_2 43
#define infrared_2_1 44
#define infrared_2_2 45

#define infrared_graber_1 40
#define infrared_graber_2 41

extern int rate, rate1, t, flag, flag1, flag_TIME, flag_TIME1, flag_RFID, infrared_flag, infrared_flag1,flag_back;
extern int sensor_1[4], sensor_2[4], sensor_3[4], sensor_4[4], infrared_front[2],infrared_graber;
//extern uint8_t data[4];
int linewalking_delay(int Direction, int rate, int rate_adjust, bool Time);

void sensors_init() {
  pinMode(sensor_front_1, INPUT);
  pinMode(sensor_front_2, INPUT);
  pinMode(sensor_front_3, INPUT);
  pinMode(sensor_front_4, INPUT);
  pinMode(sensor_back_1, INPUT);
  pinMode(sensor_back_2, INPUT);
  pinMode(sensor_back_3, INPUT);
  pinMode(sensor_back_4, INPUT);
  pinMode(sensor_left_1, INPUT);
  pinMode(sensor_left_2, INPUT);
  pinMode(sensor_left_3, INPUT);
  pinMode(sensor_left_4, INPUT);
  pinMode(sensor_right_1, INPUT);
  pinMode(sensor_right_2, INPUT);
  pinMode(sensor_right_3, INPUT);
  pinMode(sensor_right_4, INPUT);

  pinMode(infrared_1_1, INPUT);
  pinMode(infrared_1_2, INPUT);
  pinMode(infrared_2_1, INPUT);
  pinMode(infrared_2_2, INPUT);

  pinMode(infrared_graber_1, INPUT);
  pinMode(infrared_graber_2, INPUT);
}

void sensor_read(int Direction) { //红外传感器分四组，在车上前后左右固定；记录传感器数据的数组顺时针编号，1为前，2为右，3为后，4为左，但相对于车不固定，巡线方向视为前，顺时针依次为巡线方向的右，后，左
  //int Direct=(Direction+Direction_flag)%4;
  switch (Direction) {
    case 0:
      sensor_1[0] = digitalRead(sensor_front_1);
      sensor_1[1] = digitalRead(sensor_front_2);
      sensor_1[2] = digitalRead(sensor_front_3);
      sensor_1[3] = digitalRead(sensor_front_4);

      sensor_3[0] = digitalRead(sensor_back_1);
      sensor_3[1] = digitalRead(sensor_back_2);
      sensor_3[2] = digitalRead(sensor_back_3);
      sensor_3[3] = digitalRead(sensor_back_4);

      sensor_4[0] = digitalRead(sensor_left_1);
      sensor_4[1] = digitalRead(sensor_left_2);
      sensor_4[2] = digitalRead(sensor_left_3);
      sensor_4[3] = digitalRead(sensor_left_4);

      sensor_2[0] = digitalRead(sensor_right_1);
      sensor_2[1] = digitalRead(sensor_right_2);
      sensor_2[2] = digitalRead(sensor_right_3);
      sensor_2[3] = digitalRead(sensor_right_4);
      //infrared_front[0]=digitalRead(infrared_mask_2);
      //infrared_front[1]=digitalRead(infrared_mask_1);
      break;

    case 1:
      sensor_4[0] = digitalRead(sensor_front_1);
      sensor_4[1] = digitalRead(sensor_front_2);
      sensor_4[2] = digitalRead(sensor_front_3);
      sensor_4[3] = digitalRead(sensor_front_4);

      sensor_2[0] = digitalRead(sensor_back_1);
      sensor_2[1] = digitalRead(sensor_back_2);
      sensor_2[2] = digitalRead(sensor_back_3);
      sensor_2[3] = digitalRead(sensor_back_4);

      sensor_3[0] = digitalRead(sensor_left_1);
      sensor_3[1] = digitalRead(sensor_left_2);
      sensor_3[2] = digitalRead(sensor_left_3);
      sensor_3[3] = digitalRead(sensor_left_4);

      sensor_1[0] = digitalRead(sensor_right_1);
      sensor_1[1] = digitalRead(sensor_right_2);
      sensor_1[2] = digitalRead(sensor_right_3);
      sensor_1[3] = digitalRead(sensor_right_4);

      infrared_front[0] = digitalRead(infrared_2_1);
      infrared_front[1] = digitalRead(infrared_2_2);
      infrared_graber=digitalRead(infrared_graber_1);
      break;

    case 2:
      sensor_3[0] = digitalRead(sensor_front_1);
      sensor_3[1] = digitalRead(sensor_front_2);
      sensor_3[2] = digitalRead(sensor_front_3);
      sensor_3[3] = digitalRead(sensor_front_4);

      sensor_1[0] = digitalRead(sensor_back_1);
      sensor_1[1] = digitalRead(sensor_back_2);
      sensor_1[2] = digitalRead(sensor_back_3);
      sensor_1[3] = digitalRead(sensor_back_4);

      sensor_2[0] = digitalRead(sensor_left_1);
      sensor_2[1] = digitalRead(sensor_left_2);
      sensor_2[2] = digitalRead(sensor_left_3);
      sensor_2[3] = digitalRead(sensor_left_4);

      sensor_4[0] = digitalRead(sensor_right_1);
      sensor_4[1] = digitalRead(sensor_right_2);
      sensor_4[2] = digitalRead(sensor_right_3);
      sensor_4[3] = digitalRead(sensor_right_4);
      break;

    case 3:
      sensor_2[0] = digitalRead(sensor_front_1);
      sensor_2[1] = digitalRead(sensor_front_2);
      sensor_2[2] = digitalRead(sensor_front_3);
      sensor_2[3] = digitalRead(sensor_front_4);

      sensor_4[0] = digitalRead(sensor_back_1);
      sensor_4[1] = digitalRead(sensor_back_2);
      sensor_4[2] = digitalRead(sensor_back_3);
      sensor_4[3] = digitalRead(sensor_back_4);

      sensor_1[0] = digitalRead(sensor_left_1);
      sensor_1[1] = digitalRead(sensor_left_2);
      sensor_1[2] = digitalRead(sensor_left_3);
      sensor_1[3] = digitalRead(sensor_left_4);

      sensor_3[0] = digitalRead(sensor_right_1);
      sensor_3[1] = digitalRead(sensor_right_2);
      sensor_3[2] = digitalRead(sensor_right_3);
      sensor_3[3] = digitalRead(sensor_right_4);

      infrared_front[0] = digitalRead(infrared_1_1);
      infrared_front[1] = digitalRead(infrared_1_2);
      infrared_graber=digitalRead(infrared_graber_2);
      break;

    default: ;//Serial.println("switch5 error");
  }
}

int linewalking(int Direction, int rate, int rate_adjust, bool Rfid, bool Time,bool graber) {
  int Direct = (12 + Direction - Direction_flag) % 4;
  int FLAG1 = 0, FLAG2 = 0;
  int count=0;
  while (1) { //1为黑线的返回值，0为白线的返回值
    if(flag_back)delay(10);
    sensor_read(Direct);      //可以考虑读到RFID停止        左边进入横向黑线正中 右边进入横向黑线正中
    /*
      if(!sensor_1[0]&&!sensor_1[1]&!sensor_1[2]&&!sensor_1[3]){Serial.println("!");//前方无黑线（后方无黑线先不考虑）
      if(!sensor_2[0]&&!sensor_2[1]&&!sensor_2[2]&&!sensor_2[3]  &&  !sensor_4[0]&&!sensor_4[1]&!sensor_4[2]&&!sensor_4[3])break;
      }
    */
    if (Time) {
      if (flag_TIME) {
        //Serial.println("!!!\n");
        flag_TIME = 0;
        break;
      }
    }
    //else Serial.println("&&&&&&&");
    if (Time) {
      if (!interrupt_flag) {
        if(count == 0){count ++;interrupt();}
      }
      
      //else Serial.println("wait\n");
    }
    
    if (flag_TIME1) {
      if (sensor_4[3]) {
        flag = 1;
        FLAG2 = 1;
      }
      if (sensor_2[0]) {
        flag = 1;
        FLAG1 = 1;
      }

      if (flag) {
        rate=58;
        flag_mask=1;
        if (FLAG1 == 1 && FLAG2 == 1) {
          if (!sensor_4[3] && !sensor_2[0]) {
            flag = FLAG1 = FLAG2 = 0;
            flag_TIME1 = 0;
            if (!interrupt_flag)interrupt1();
            //Serial.println("^");
            break;
          }
        }
        else if (FLAG1 == 1) {
          if (!sensor_2[0]) {
            flag = FLAG1 = FLAG2 = 0;
            flag_TIME1 = 0;
            if (!interrupt_flag)interrupt1();
            //Serial.println("^^");
            break;
          }
        }
        else if (FLAG2 == 1) {
          if (!sensor_4[3]) {
            flag = FLAG1 = FLAG2 = 0;
            flag_TIME1 = 0;
            if (!interrupt_flag)interrupt1();
            //Serial.println("^^^");
            //Serial.print(sensor_4[0]);
            //Serial.print(sensor_4[1]);
            //Serial.print(sensor_4[2]);
            //Serial.print(sensor_4[3]);
            break;
          }
        }
        else;

      }
    }
    if (!infrared_front[0] || !infrared_front[1]) {
      //Serial.println("!!*\n");
      infrared_flag = 1;
      infrared_front[1] = infrared_front[0] = 1;
      break;
    }

    if (Rfid) {
      //Serial.println("!!!!\n");
      if (Direct == 3) {
        flag_RFID = searchforRFID_0();
        if (flag_RFID == -1)flag_RFID = searchforRFID_0();
        if (flag_RFID == -1)flag_RFID = searchforRFID_0();
        if (flag_RFID == -1) {
          Stop();
          for (;;);
        }
      }
      else if (Direct == 1) {
        flag_RFID = searchforRFID_1();
        if (flag_RFID == -1)flag_RFID = searchforRFID_1();
        if (flag_RFID == -1)flag_RFID = searchforRFID_1();
        if (flag_RFID == -1) {
          Stop();
          for (;;);
        }
      }
      else;

      if (flag_RFID) {
         //Serial.println("$$");
        //flag_RFID=0;//此处不置0，外部使用完后置0
        break;
      }
    }

    if(graber){
      if(!infrared_graber){break;}
    }

    //以上为控制停止

    if (!sensor_1[0] && sensor_1[3]  &&  !sensor_3[0] && sensor_3[3]) { //偏逆时针
      if (!((sensor_1[0] && sensor_1[3])  ||  (sensor_3[0] && sensor_3[3]))) {
        clockwise(rate / 2);
        continue;
      }
    }      //把&&换成了||，待测试
    if (sensor_1[0] && !sensor_1[3]  &&  sensor_3[0] && !sensor_3[3]) { //偏顺时针
      if (!((sensor_1[0] && sensor_1[3])  ||  (sensor_3[0] && sensor_3[3]))) {
        anticlockwise(rate / 2);
        continue;
      }
    }

    if (!sensor_1[0] && sensor_1[3]  ||  sensor_3[0] && !sensor_3[3]) { //偏左
      if (!((sensor_1[0] && sensor_1[3])  ||  (sensor_3[0] && sensor_3[3]))) {
        switch (Direct) {
          case 0: adjust_0_right(rate, rate_adjust); break;
          case 1: adjust_1_right(rate, rate_adjust); break;
          case 2: adjust_2_right(rate, rate_adjust); break;
          case 3: adjust_3_right(rate, rate_adjust); break;
          default: ;//Serial.println("switch8 error");
            continue;
        }
      }
    }//把&&换成了||，待测试
    if (sensor_1[0] && !sensor_1[3]  ||  !sensor_3[0] && sensor_3[3]) { //偏右
      if (!((sensor_1[0] && sensor_1[3])  ||  (sensor_3[0] && sensor_3[3]))) {
        switch (Direct) {
          case 0: adjust_0_left(rate, rate_adjust); break;
          case 1: adjust_1_left(rate, rate_adjust); break;
          case 2: adjust_2_left(rate, rate_adjust); break;
          case 3: adjust_3_left(rate, rate_adjust); break;
          default: ;//Serial.println("switch15 error");
            continue;
        }
      }
    }

    if (sensor_1[0] && sensor_1[1] && sensor_1[2] && sensor_1[3]  &&  !sensor_3[0] && !sensor_3[3]  ||  sensor_3[0] && sensor_3[1] && sensor_3[2] && sensor_3[3]  &&  !sensor_1[0] && !sensor_1[3]  ||  !sensor_1[0] && !sensor_1[3] && !sensor_3[0] && !sensor_3[3]) //正前方检测到横向黑线还需继续前进
    {
      switch (Direct) {
        case 0: forward(rate); break;
        case 1: go_right(rate); break;
        case 2: backward(rate); break;
        case 3: go_left(rate); break;
        default: ;//Serial.println("switch8 error");
      }
      continue;
    }
    /*
      switch(Direct){
        case 0:forward(rate);break;
        case 1:go_right(rate);break;
        case 2:backward(rate);break;
        case 3:go_left(rate);break;
        default:Serial.println("switch8 error");
      }
    */
    /*
      if(!sensor_1[0]&&!sensor_1[1]&&!sensor_1[2]&&!sensor_1[3]){//前方为白线需判定是否停止
      if(flag1){flag1=0;break;}
      if(!flag1){flag1=1;}
      }
    */
    
  }
  
  if (flag_back) {
    switch (Direct) {
      case 0: backward(100); delay(120); break;
      case 1: go_left(100); delay(120); break;
      case 2: forward(100); delay(120); break;
      case 3: go_right(100); delay(120); break;
      default: ;//Serial.println("switch8 error");
    }
  }
  
  t=400;
  if(infrared_flag){Stop();delay(100);linewalking_delay(Direction,100,38,TIME);}
  t=700;
  flag_mask=0;
  infrared_flag = 0;
  Stop();
  if (Direction == 0)return 1;
  else if (Direction == 2)return -1;
  else return 0;
}

int linewalking_delay(int Direction, int rate, int rate_adjust, bool Time) {
  int Direct = (12 + Direction - Direction_flag) % 4;
  int FLAG1 = 0, FLAG2 = 0;
  int count=0;
  while (1) { //1为黑线的返回值，0为白线的返回值
    //delay(10);
    sensor_read(Direct);      //可以考虑读到RFID停止        左边进入横向黑线正中 右边进入横向黑线正中
    if (Time) {
      if (flag_TIME) {
        //Serial.println("!!!\n");
        flag_TIME = 0;
        break;
      }
    }
    if (Time) {
      if (!interrupt_flag) {
        if (!interrupt_flag) {
        if(count == 0){count ++;interrupt();}
      }
      }
      //else Serial.println("wait\n");
    }

    

    if (sensor_4[3]) {
        flag = 1;
        FLAG2 = 1;
      }
      if (sensor_2[0]) {
        flag = 1;
        FLAG1 = 1;
      }

      if (flag) {
        rate=58;
        flag_mask=1;
        if (FLAG1 == 1 && FLAG2 == 1) {
          if (!sensor_4[3] && !sensor_2[0]) {
            flag = FLAG1 = FLAG2 = 0;
            flag_TIME1 = 0;
            //if (!interrupt_flag)interrupt1();
            //Serial.println("^");
            break;
          }
        }
        else if (FLAG1 == 1) {
          if (!sensor_2[0]) {
            flag = FLAG1 = FLAG2 = 0;
            flag_TIME1 = 0;
            //if (!interrupt_flag)interrupt1();
            //Serial.println("^^");
            break;
          }
        }
        else if (FLAG2 == 1) {
          if (!sensor_4[3]) {
            flag = FLAG1 = FLAG2 = 0;
            flag_TIME1 = 0;
            //if (!interrupt_flag)interrupt1();
            //Serial.println("^^^");
            //Serial.print(sensor_4[0]);
            //Serial.print(sensor_4[1]);
            //Serial.print(sensor_4[2]);
            //Serial.print(sensor_4[3]);
            break;
          }
        }
        else;

      }
    
    //以上为控制停止

    if (!sensor_1[0] && sensor_1[3]  &&  !sensor_3[0] && sensor_3[3]) { //偏逆时针
      if (!((sensor_1[0] && sensor_1[3])  ||  (sensor_3[0] && sensor_3[3]))) {
        clockwise(rate / 2);
        continue;
      }
    }      //把&&换成了||，待测试
    if (sensor_1[0] && !sensor_1[3]  &&  sensor_3[0] && !sensor_3[3]) { //偏顺时针
      if (!((sensor_1[0] && sensor_1[3])  ||  (sensor_3[0] && sensor_3[3]))) {
        anticlockwise(rate / 2);
        continue;
      }
    }

    if (!sensor_1[0] && sensor_1[3]  ||  sensor_3[0] && !sensor_3[3]) { //偏左
      if (!((sensor_1[0] && sensor_1[3])  ||  (sensor_3[0] && sensor_3[3]))) {
        switch (Direct) {
          case 0: adjust_0_right(rate, rate_adjust); break;
          case 1: adjust_1_right(rate, rate_adjust); break;
          case 2: adjust_2_right(rate, rate_adjust); break;
          case 3: adjust_3_right(rate, rate_adjust); break;
          default: ;//Serial.println("switch8 error");
            continue;
        }
      }
    }//把&&换成了||，待测试
    if (sensor_1[0] && !sensor_1[3]  ||  !sensor_3[0] && sensor_3[3]) { //偏右
      if (!((sensor_1[0] && sensor_1[3])  ||  (sensor_3[0] && sensor_3[3]))) {
        switch (Direct) {
          case 0: adjust_0_left(rate, rate_adjust); break;
          case 1: adjust_1_left(rate, rate_adjust); break;
          case 2: adjust_2_left(rate, rate_adjust); break;
          case 3: adjust_3_left(rate, rate_adjust); break;
          default: ;//Serial.println("switch15 error");
            continue;
        }
      }
    }

    if (sensor_1[0] && sensor_1[1] && sensor_1[2] && sensor_1[3]  &&  !sensor_3[0] && !sensor_3[3]  ||  sensor_3[0] && sensor_3[1] && sensor_3[2] && sensor_3[3]  &&  !sensor_1[0] && !sensor_1[3]  ||  !sensor_1[0] && !sensor_1[3] && !sensor_3[0] && !sensor_3[3]) //正前方检测到横向黑线还需继续前进
    {
      switch (Direct) {
        case 0: forward(rate); break;
        case 1: go_right(rate); break;
        case 2: backward(rate); break;
        case 3: go_left(rate); break;
        default: ;//Serial.println("switch8 error");
      }
      continue;
    }
    
    
  }
  /*
  if (!infrared_flag) {
    switch (Direct) {
      case 0: backward(170); delay(200); break;
      case 1: go_left(170); delay(200); break;
      case 2: forward(170); delay(200); break;
      case 3: go_right(170); delay(200); break;
      default: Serial.println("switch8 error");
    }
  }
  */
  if (flag_back) {
    switch (Direct) {
      case 0: backward(100); delay(120); break;
      case 1: go_left(100); delay(120); break;
      case 2: forward(100); delay(120); break;
      case 3: go_right(100); delay(120); break;
      default: ;//Serial.println("switch8 error");
    }
  }
  flag_mask=0;
  Stop();
  if (Direction == 0)return 1;
  else if (Direction == 2)return -1;
  else return 0;
}
int linewalking_nosensor(int Direction) {
  int Direct = (12 + Direction - Direction_flag) % 4;
  int FLAG1 = 0, FLAG2 = 0;
  while (1) {
    sensor_read(Direct);
    /*
      if(!flag){if(sensor_4[3]||sensor_2[0])flag=1;}
      if(!sensor_4[0]&&sensor_4[1]&&!sensor_4[3]||!sensor_4[0]&&sensor_4[2]&&!sensor_4[3]  ||  !sensor_2[0]&&sensor_2[1]&&!sensor_2[3]||!sensor_2[0]&&sensor_2[2]&&!sensor_2[3]){//左或右走到线上有一侧走到线上，可以进行左右巡线；或者前侧扫到全白则停止，不严谨
      if(flag){flag=0;break;}
      }
    */
    if (sensor_4[3]) {
      //Serial.println("!");
      flag = 1;
      FLAG2 = 1;
    }
    if (sensor_2[0]) {
      //Serial.println("!!");
      flag = 1;
      FLAG1 = 1;
    }
    if (flag) {
      //Serial.println("!!!");
      if ((!sensor_4[0] && sensor_4[1] && !sensor_4[3] || !sensor_4[0] && sensor_4[2] && !sensor_4[3]) || (!sensor_2[0] && sensor_2[1] && !sensor_2[3] || !sensor_2[0] && sensor_2[2] && !sensor_2[3])) {
        flag = 0;
        FLAG1 = FLAG2 = 0;
        break;
      }

      /*
        if(FLAG1==1&&FLAG2==1){
        if((!sensor_4[0]&&sensor_4[1]&&!sensor_4[3]||!sensor_4[0]&&sensor_4[2]&&!sensor_4[3])&&(!sensor_2[0]&&sensor_2[1]&&!sensor_2[3]||!sensor_2[0]&&sensor_2[2]&&!sensor_2[3])){flag=0;FLAG1=FLAG2=0;break;}
        }
        else if(FLAG1==1){
        if(!sensor_2[0]&&sensor_2[1]&&!sensor_2[3]||!sensor_2[0]&&sensor_2[2]&&!sensor_2[3]){flag=0;FLAG1=FLAG2=0;break;}
        }
        else{
        if(!sensor_4[0]&&sensor_4[1]&&!sensor_4[3]||!sensor_4[0]&&sensor_4[2]&&!sensor_4[3]){flag=0;FLAG1=FLAG2=0;break;}
        }
      */
    }
    switch (Direct) {
      case 0: forward(rate); break;
      case 1: go_right(rate); break;
      case 2: backward(rate); break;
      case 3: go_left(rate); break;
      default: ;//Serial.println("switch9 error");
    }
  }
  switch (Direct) {
    case 0: backward(rate); delay(300); break;
    case 1: go_left(rate); delay(300); break;
    case 2: forward(rate); delay(300); break;
    case 3: go_right(rate); delay(300); break;
    default: ;//Serial.println("switch8 error");
  }
  Stop();
  if (Direction == 0)return 1;
  else if (Direction == 2)return -1;
  else return 0;
}

void rotate(int clock_or_anticlock) { //1为顺时针，0为逆时针
  //int Direct=(Direction+Direction_flag)%4;
  if (clock_or_anticlock) {
    while (1) {
      sensor_read((Direction_flag + 1) % 4);
      if (!flag) {
        if (sensor_4[3] || sensor_2[3])flag = 1;
      }
      if (flag) {
        if ((!sensor_4[0] && sensor_4[1] && !sensor_4[3] || !sensor_4[0] && sensor_4[2] && !sensor_4[3])  ||  (!sensor_2[0] && sensor_2[1] && !sensor_2[3] || !sensor_2[0] && sensor_2[2] && !sensor_2[3])) { //左或右走到线上有一侧走到线上，可以进行左右巡线；或者前侧扫到全白则停止，不严谨
          flag = 0; break;
        }
      }
      clockwise(40); //速度待定
    }
    //delay(250);
    Stop();
  }
  else {
    while (1) {
      sensor_read((Direction_flag + 1) % 4);
      if (!flag) {
        if (sensor_4[3] || sensor_2[3])flag = 1;
      }
      if (!sensor_4[0] && sensor_4[1] && !sensor_4[3] || !sensor_4[0] && sensor_4[2] && !sensor_4[3]  ||  !sensor_2[0] && sensor_2[1] && !sensor_2[3] || !sensor_2[0] && sensor_2[2] && !sensor_2[3]) { //左或右走到线上有一侧走到线上，可以进行左右巡线；或者前侧扫到全白则停止，不严谨
        if (flag) {
          flag = 0;
          break;
        }
      }
      anticlockwise(40); //速度待定
    }
    //delay(250);
    Stop();
  }
}

void rotate1(int clock_or_anticlock) { //1为顺时针，0为逆时针
  //int Direct=(Direction+Direction_flag)%4;
  if (clock_or_anticlock) {
    while (1) {
      sensor_read(0);
      if (!flag) {
        if (sensor_1[3])flag = 1;
      }
      if (flag) {
        if (!sensor_1[0] && sensor_1[1] && !sensor_1[3] || !sensor_1[0] && sensor_1[2] && !sensor_1[3]) { //左或右走到线上有一侧走到线上，可以进行左右巡线；或者前侧扫到全白则停止，不严谨
          flag = 0; break;
        }
      }
      clockwise(45); //速度待定
    }
    //delay(250);
    Stop();
  }
  else {
    while (1) {
      sensor_read(0);
      if (!flag) {
        if (sensor_1[0])flag = 1;
      }
      if (flag) {
        if (!sensor_1[0] && sensor_1[1] && !sensor_1[3] || !sensor_1[0] && sensor_1[2] && !sensor_1[3]) { //左或右走到线上有一侧走到线上，可以进行左右巡线；或者前侧扫到全白则停止，不严谨
          flag = 0; break;
        }
      }
      anticlockwise(45); //速度待定
    }
    //delay(250);
    Stop();
  }
}
#endif
