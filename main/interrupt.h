#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include <MsTimer2.h>

extern int flag_TIME,flag_TIME1,t,t1,interrupt_flag;
void flag_Time();
void flag_Time1();
void interrupt(){
  
  MsTimer2::set(t, flag_Time); // 100ms 触发一次中断，调用函数inter()
  MsTimer2::start();    //开启中断
  interrupt_flag=1;
  //Serial.println("interrupt ok\n");
}

void interrupt1(){
  
  MsTimer2::set(t1, flag_Time1); // 100ms 触发一次中断，调用函数inter()
  MsTimer2::start();    //开启中断
  interrupt_flag=1;
  //Serial.println("interrupt1 ok\n");
}
void flag_Time(){
  
  flag_TIME=1;
  MsTimer2::stop(); //开启中断
  interrupt_flag=0;
  //Serial.println("interrupt over\n");
  return;
}
void flag_Time1(){
  
  flag_TIME1=1;
  MsTimer2::stop();    //开启中断
  interrupt_flag=0;
  //Serial.println("interrupt1 over\n");
  return;
}

#endif
