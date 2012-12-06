#pragma config(Sensor, S1,     MAX127,              sensorI2CCustomStd)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: maxim-max127-test1.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * maxim-max127.h provides an API for the MAXIM MAX127 ADC.  This program
 * demonstrates how to use that API.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 08 March 2009
 * version 0.1
 */

#include "drivers/maxim-max127.h"

task main() {
  int _chVal = 0;
  nxtDisplayTextLine(3, "MAX127");
  nxtDisplayTextLine(4, "Test prog");
  wait1Msec(1000);
  eraseDisplay();

  while(true) {
    eraseDisplay();
    for (int i = 0; i < 8; i++) {
      _chVal = MAX127readChan(MAX127, MAX127_I2C_ADDR, i);
      // if the return value is < 0 then an error occurred
      if (_chVal < 0) {
        nxtDisplayTextLine(4, "ERROR!!");
        wait1Msec(2000);
        StopAllTasks();
      }
      nxtDisplayTextLine(i, "CH[%d]: %d", i, _chVal);
    }
    wait1Msec(100);
  }
}

/*
 * $Id: maxim-max127-test1.c 123 2012-11-02 16:35:15Z xander $
 */
