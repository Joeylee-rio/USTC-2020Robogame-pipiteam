#ifndef wheel_H_
#define wheel_H_
#include"Arduino.h"

#define ENA 5  //电机接口
#define ENB 2
#define ENC 3
#define IN1 26
#define IN2 27
#define IN3 22
#define IN4 23
#define IN5 24
#define IN6 25


#define VX_VALUE           (0.5f)
#define VY_VALUE           (sqrt(3)/2.f)      
#define L_value            (20*0.01f)  
#define RADIUS_value       (1.0/12.5*0.01f)//待测定

extern float motor_one,motor_two,motor_three;
extern int motor_1,motor_2,motor_3,Direction_flag,rate_adjust,flag_mask;

void wheels_init();
void wheel(int wheelnum,int sp,int rotation);//单个轮子
void move_control(float vx,float vy,float vz);
void forward(int sp);
void backward(int sp);
void go_left(int sp);
void go_right(int sp);
void anticlockwise(int sp);
void clockwise(int sp);
void Stop();

void wheels_init(){
  pinMode(ENA,OUTPUT);//PWM
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,OUTPUT);//PWM
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENC,OUTPUT);//PWM
  pinMode(IN5,OUTPUT);
  pinMode(IN6,OUTPUT);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  analogWrite(ENC, 0);
  
}
void wheel(int wheelnum,int sp,int rotation){//rotation 1为正转，0为停止，-1为反转
   switch(wheelnum){
    case 1:
    switch(rotation){
      case 1:analogWrite(ENA, sp);digitalWrite(IN1, HIGH);digitalWrite(IN2, LOW);break;
      case -1:analogWrite(ENA, sp);digitalWrite(IN1, LOW);digitalWrite(IN2, HIGH);break;
      case 0:analogWrite(ENA, 0);digitalWrite(IN1, LOW);digitalWrite(IN2, LOW);break;
      default:;//Serial.println("switch1 error");
      }
      break;
      
    case 2:
    switch(rotation){
      case 1:analogWrite(ENB, sp);digitalWrite(IN3, HIGH);digitalWrite(IN4, LOW);break;
      case -1:analogWrite(ENB, sp);digitalWrite(IN3, LOW);digitalWrite(IN4, HIGH);break;
      case 0:analogWrite(ENB, 0);digitalWrite(IN3, LOW);digitalWrite(IN4, LOW);break;
      default:;//Serial.println("switch2 error");
      }
      break;

    case 3:
    switch(rotation){
      case 1:analogWrite(ENC, sp);digitalWrite(IN5, HIGH);digitalWrite(IN6, LOW);break;
      case -1:analogWrite(ENC, sp);digitalWrite(IN5, LOW);digitalWrite(IN6, HIGH);break;
      case 0:analogWrite(ENC, 0);digitalWrite(IN5, LOW);digitalWrite(IN6, LOW);break;
      default:;//Serial.println("switch3 error");
    }break;

    default:;//Serial.println("switch4 error");
  }
}

//int motor_one,motor_two,motor_three;
void move_control(float vx,float vy,float vz)
{
  motor_one = (-VX_VALUE*vx + VY_VALUE*vy + L_value*vz);//Serial.print(motor_one); //三个轮待确定0.85*
  motor_two = (-VX_VALUE*vx - VY_VALUE*vy + L_value*vz);//Serial.print(motor_two);0.795*
  motor_three = (vx + L_value*vz);//Serial.print(motor_three);//*(vx>0?0.89:0.9)
  if(vx<0){
    if(!flag_mask){
      motor_1=abs(motor_one);   //rate=80时左移动加5，右减2，前移动减5，后加6
      motor_2=abs(motor_two);
      motor_3=abs(motor_three)-4;
    }
    else {
    motor_1=abs(motor_one)+11;   //rate=80时左移动加5，右减2，前移动减5，后加6
    motor_2=abs(motor_two)+11;
    motor_3=abs(motor_three);
    }
  }
  else if(vx>0){
    if(!flag_mask){ 
      motor_1=abs(motor_one)+4;   //rate=80时左移动加5，右减2，前移动减5，后加6
      motor_2=abs(motor_two)+4;
      motor_3=abs(motor_three)-4;
    }
    else {
    motor_1=abs(motor_one)+11;   //rate=80时左移动加5，右减2，前移动减5，后加6
    motor_2=abs(motor_two)+11;
    motor_3=abs(motor_three);
    }
  }
  else if(vy<0){
    motor_1=abs(motor_one);   //rate=80时左移动加5，右减2，前移动减5，后加6
    motor_2=abs(motor_two);
    motor_3=abs(motor_three);
    }
  else if(vy>0){
    motor_1=abs(motor_one);   //rate=80时左移动加5，右减2，前移动减5，后加6
    motor_2=abs(motor_two);
    motor_3=abs(motor_three);
    }
  else {
    motor_1=abs(motor_one);   //rate=80时左移动加5，右减2，前移动减5，后加6
    motor_2=abs(motor_two);
    motor_3=abs(motor_three);
    }
  
  if(motor_one>0) wheel(1,motor_1,1);
  else if(motor_one<0) wheel(1,motor_1,-1);
  else wheel(1,motor_1,0);

  if(motor_two>0) {wheel(2,motor_2,1);}
  else if(motor_two<0) {wheel(2,motor_2,-1);}
  else {wheel(2,motor_2,0);}
  
  if(motor_three>0) wheel(3,motor_3,1);
  else if(motor_three<0) wheel(3,motor_3,-1);
  else wheel(3,motor_3,0);
  
  
  
}

void forward(int sp){//同时控制前后，正为前，负为后
  move_control(sp*(-1),0,0);//向前时2号轮在右，3号轮在前，1号轮在后
}
void backward(int sp){
  move_control(sp,0,0);
}

void go_left(int sp){//同时控制左右，正为左
  move_control(0,sp*(-1),0);
}

void go_right(int sp){//同时控制左右，正为左
  move_control(0,sp,0);
}

void adjust_0_left(int sp,int rate_adjust){
  move_control(sp*(-1),rate_adjust*(-1),0);
}

void adjust_0_right(int sp,int rate_adjust){
  move_control(sp*(-1),rate_adjust,0);
}

void adjust_1_left(int sp,int rate_adjust){
  move_control(rate_adjust*(-1),sp,0);
}

void adjust_1_right(int sp,int rate_adjust){
  move_control(rate_adjust,sp,0);
}

void adjust_2_left(int sp,int rate_adjust){
  move_control(sp,rate_adjust,0);
}

void adjust_2_right(int sp,int rate_adjust){
  move_control(sp,rate_adjust*(-1),0);
}

void adjust_3_left(int sp,int rate_adjust){
  move_control(rate_adjust,sp*(-1),0);
}

void adjust_3_right(int sp,int rate_adjust){
  move_control(rate_adjust*(-1),sp*(-1),0);
}
/*
void Move(int D,int sp){
  int Direct;
  if(!Direction_flag)Direct=D;
  else Direct=(D+3)%5;
  switch(Direct){
        case 4:go_left(sp);break;
        case 1:forward(sp);break;
        case 2:go_right(sp);break;
        case 3:backward(sp);break;
        default:Serial.println("switch6 error");
      }
  }
/*void clockwise(int sp){
  move_control(0,0,sp);//不确定方向sp或者-sp
}

void anticlockwise(int sp){
  move_control(0,0,sp*(-1));//不确定方向sp或者-sp
}
*/

void Stop(){
  move_control(0,0,0);
}

void anticlockwise(int sp){//注意顺时针的接口输入
  analogWrite(ENA,sp);
  analogWrite(ENB,sp);
  analogWrite(ENC,sp);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN5,LOW);
  digitalWrite(IN6,HIGH);
  
}

void clockwise(int sp){
  analogWrite(ENA,sp);
  analogWrite(ENB,sp);
  analogWrite(ENC,sp);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(IN5,HIGH);
  digitalWrite(IN6,LOW);
  
}

#endif
