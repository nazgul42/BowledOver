#pragma config(Sensor, S1,     MSAC,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-accelerometer-test1.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * mindsensors-accelerometer.h provides an API for the Mindsensors Acceleration Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments<br>
 *        Make use of the new range defines
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 28 November 2009
 * version 0.2
 */

#include "drivers/mindsensors-accelerometer.h"

task main () {
  int _x_accel = 0;
  int _y_accel = 0;
  int _z_accel = 0;

  int _x_tilt = 0;
  int _y_tilt = 0;
  int _z_tilt = 0;

  string _tmp;

  nxtDisplayCenteredTextLine(0, "Mindsensors");
  nxtDisplayCenteredBigTextLine(1, "ACCEL-Nx");
  nxtDisplayCenteredTextLine(3, "Test 1");
  wait1Msec(2000);

  // There are four ranges the ACCL-Nx can measure in
  // up to 2.5G - MSAC_RANGE_2_5
  // up to 3.3G - MSAC_RANGE_3_3
  // up to 6.7G - MSAC_RANGE_6_7
  // up to 10G  - MSAC_RANGE_10
  MSACsetRange(MSAC, MSAC_RANGE_10);

  PlaySound(soundBeepBeep);
  while(bSoundActive) EndTimeSlice();

  while (true) {
    eraseDisplay();


    // Read the tilt data from the sensor
    if (!MSACreadTilt(MSAC, _x_tilt, _y_tilt, _z_tilt)) {
      nxtDisplayTextLine(4, "ERROR!!");
      wait1Msec(2000);
      StopAllTasks();
    }

    // Read the acceleration data from the sensor
    if (!MSACreadAccel(MSAC, _x_accel, _y_accel, _z_accel)) {
      nxtDisplayTextLine(4, "ERROR!!");
      wait1Msec(2000);
      StopAllTasks();
    }

    nxtDisplayTextLine(0,"MSAC Test 1");

    // We can't provide more than 2 parameters to nxtDisplayTextLine(),
    // so we'll do in two steps using StringFormat()
    nxtDisplayTextLine(2, "Tilt X    Y    Z");
    StringFormat(_tmp, "  %4d %4d", _x_tilt, _y_tilt);
    nxtDisplayTextLine(3, "%s %4d", _tmp, _z_tilt);

    nxtDisplayTextLine(4, "Acceleration:");
    nxtDisplayTextLine(5, "X: %5d mG", _x_accel);
    nxtDisplayTextLine(6, "Y: %5d mG", _y_accel);
    nxtDisplayTextLine(7, "Z: %5d mG", _z_accel);
    wait1Msec(100);
  }
}

/*
 * $Id: mindsensors-accelerometer-test1.c 123 2012-11-02 16:35:15Z xander $
 */
