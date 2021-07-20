#include "graber.h"
#include "linewalking1.h"
#include "myRFID.h"

extern int Location, Direction_flag, red;

void find_yellow_left() {
  while (!(Graber1 && Graber2)) {
    t = 650; linewalking(1, rate, rate_adjust, NORFID, TIME, NOGRABER);
    flag_mask = 1;  linewalking(1, 60, 20, RFID, NOTIME, NOGRABER); flag_mask = 0; infrared_flag = 0;
    Patient[Location] = flag_RFID; //返回0的话为出错，还未考虑该情况
    if (flag_RFID == 3)red = Location;
    flag_RFID = 0;
    if (Patient[Location] == 2) {
      if ((3 + Direction_flag) % 4 == 1) {
        Grab_up(1);
        Graber1 = 1;
        rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4; rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4;
      }
      else if ((3 + Direction_flag + 12) % 4 == 3) {
        Grab_up(2);
        Graber2 = 1;
      }
      else;
    }
    if (!(Graber1 && Graber2)) {
      linewalking(3, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
      Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
      Location_farthest = Location;
    }
  }
}

void transfer_yellow_left() {
  switch (Location) {
    case 4:
    case 5:
    case 6:
      linewalking(3, rate, rate_adjust, NORFID, NOTIME, NOGRABER); //来到中线
      while (Location > 4)Location += linewalking(2, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
      while (Graber1 || Graber2) {
        t = 600; linewalking(3, rate, rate_adjust, NORFID, TIME, NOGRABER);delay(50);
        flag_mask = 1;  linewalking(3, 60, 20, NORFID, NOTIME, GRABER); flag_mask = 0; infrared_flag = 0;
        if (infrared_graber) {
          if (Graber1) {
            Grab_down(1);
            Graber1 = 0;
            rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4; rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4;
          }
          else {
            Grab_down(2);
            Graber2 = 0;
          }
        }
        infrared_graber = 0;
        if (Graber1 || Graber2) {
          linewalking(1, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
          Location += linewalking(2, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
        }
      }
      linewalking(1, rate, rate_adjust, NORFID, NOTIME, NOGRABER); //回到中线
      delay(100);
      break;

    case 2:
      linewalking(3, rate, rate_adjust, NORFID, NOTIME, NOGRABER); //来到中线
      while (Graber1 || Graber2) {
        t = 600; linewalking(3, rate, rate_adjust, NORFID, TIME, NOGRABER);delay(50); 
        flag_mask = 1;  linewalking(3, 60, 20, NORFID, NOTIME, GRABER); flag_mask = 0; infrared_flag = 0;
        if (infrared_graber) {
          if (Graber1) {
            Grab_down(1);
            Graber1 = 0;
            rotate(0); Direction_flag --; rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4;;
          }
          else {
            Grab_down(2);
            Graber2 = 0;
          }
        }
        infrared_graber = 0;
        if (Graber1 || Graber2) {
          linewalking(1, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
          Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
        }
      }
      linewalking(1, rate, rate_adjust, NORFID, NOTIME, NOGRABER); //回到中线
      delay(100);
      break;

    case 3:
      linewalking(3, rate, rate_adjust, NORFID, NOTIME, NOGRABER); //来到中线
      if (!red) {
        while (Location < 2)Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER); //退到2开始
        while (Location > 2)Location += linewalking(2, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
        while (Graber1 || Graber2) {
          t = 600; linewalking(3, rate, rate_adjust, NORFID, TIME, NOGRABER);delay(50); 
          flag_mask = 1;  linewalking(3, 60, 20, NORFID, NOTIME, GRABER); flag_mask = 0; infrared_flag = 0;
          if (infrared_graber) {
            if (Graber1) {
              Grab_down(1);
              Graber1 = 0;
              rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4; rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4;
            }
            else {
              Grab_down(2);
              Graber2 = 0;
            }
          }
          infrared_graber = 0;
          if (Graber1 || Graber2) {
            linewalking(1, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
            Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
          }
        }
        linewalking(1, rate, rate_adjust, NORFID, NOTIME, NOGRABER); //回到中线
        delay(100);
      }
      else {
        while (Location < 4)Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
        while (Location > 4)Location += linewalking(2, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
        while (Graber1 || Graber2) {
          t = 600; linewalking(3, rate, rate_adjust, NORFID, TIME, NOGRABER);delay(50); 
          flag_mask = 1;  linewalking(3, 60, 20, NORFID, NOTIME, GRABER); flag_mask = 0; infrared_flag = 0;
          if (infrared_graber) {
            if (Graber1) {
              Grab_down(1);
              Graber1 = 0;
              rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4; rotate(0); Direction_flag --; if (Direction_flag < 0)Direction_flag += 4;
            }
            else {
              Grab_down(2);
              Graber2 = 0;
            }
          }
          infrared_graber = 0;
          if (Graber1 || Graber2) {
            linewalking(1, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
            Location += linewalking(2, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
          }
        }
        linewalking(1, rate, rate_adjust, NORFID, NOTIME, NOGRABER); //回到中线
        delay(100);
      }
      break;
    default: ;//Serial.println("error!");
  }
}

void transfer_red_left() {
  if (red == 0) {
    while (Location < (Location_farthest + 1))Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
    while (Location > (Location_farthest + 1))Location += linewalking(2, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
    while (!red) {
      t = 650; linewalking(1, rate, rate_adjust, NORFID, TIME, NOGRABER); 
      flag_mask = 1;  linewalking(1, 60, 20, RFID, NOTIME, NOGRABER); flag_mask = 0; infrared_flag = 0;
      if (flag_RFID == 3) {
        red = Location;
      }
      flag_RFID = 0;
      if (!red) {
        linewalking(3, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
        Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
      }
    }
  }

  else {
    while (Location < red)Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
    while (Location > red)Location += linewalking(2, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
    t = 650; linewalking(1, rate, rate_adjust, NORFID, TIME, NOGRABER); 
    flag_mask = 1;  linewalking(1, 60, 20, RFID, NOTIME, NOGRABER); flag_mask = 0; infrared_flag = 0;
    if (flag_RFID == 3) flag_RFID = 0; //再确认一遍
  }
  Grab_up(1); Graber1 = 1;
  rotate(0); Direction_flag--;
  linewalking(3, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
  while (Location < 7)Location += linewalking(0, rate, rate_adjust, NORFID, NOTIME, NOGRABER);
  while (Location > 7)Location += linewalking(2, rate, rate_adjust, NORFID, NOTIME, NOGRABER);

  flag_mask = 1;  linewalking(0, 75, 20, NORFID, NOTIME, NOGRABER); flag_mask = 0; infrared_flag = 0;

  for (; pos1 >= 0 ; pos1--) {
    servo4.write(180 - pos1);
    servo3.write(pos1);
    delay(20);
  }
  Pusher(0);
  Graber1 = 0;
}

void mask_left() {
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
  //backward(rate1); delay(t3);Stop();

}
