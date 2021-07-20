#ifndef  MYRFID_H_
#define  MYRFID_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Rfid_D_Think_M50.h>
#define BLOCK_NO 0


int searchforRFID_0() {
  Rfid_D_Think_M50 rfid( Serial1 );
  //Rfid_D_Think_M50 rfid( Serial2 );
  //Serial.begin(9600);

    // 使能天线并设置射频工作模式
    // 以 ISO15693 为例
    if( rfid.enableAntenna( rfid.ISO15693 ) ){
        //Serial.println("init_0 ok");
    }else{
        //Serial.println("init_0 failed");
        return(-1);
    }


	rfid.enableAntenna();

	uint8_t data[4]={0};
	for (int j = 0; j < 4; j++) {
      rfid.read(BLOCK_NO, data);
    }
   switch (data[1]) {
    case 1: return 3; break;
    case 2: return 2; break;
    case 3: return 1; break;
    default: return 0;
    }

	rfid.disableAntenna();
}

int searchforRFID_1() {
  //Rfid_D_Think_M50 rfid( Serial1 );
  Rfid_D_Think_M50 rfid( Serial2 );
  //Serial.begin(9600);

    // 使能天线并设置射频工作模式
    // 以 ISO15693 为例
    if( rfid.enableAntenna( rfid.ISO15693 ) ){
        //Serial.println("init_1 ok");
    }else{
        //Serial.println("init_1 failed");
        return(-1);
    }
    rfid.enableAntenna();
    uint8_t data[4]={0};
      
    rfid.read(BLOCK_NO, data);
    switch (data[1]) {
    case 1: return 3; break;
    case 2: return 2; break;
    case 3: return 1; break;
    default: return 0;
    }
  
  

  rfid.disableAntenna();
}

#endif
