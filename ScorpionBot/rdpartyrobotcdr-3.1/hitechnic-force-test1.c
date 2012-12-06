#pragma config(Sensor, S1,     HTFORCE,              sensorAnalogActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-force-test1.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * HTCS-driver.h provides an API for the HiTechnic Force Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 30 September 2012
 * version 0.1
 */

#include "drivers/hitechnic-force.h"

 /*
  =============================================================================
  main task with some testing code

 */
task main() {
  int _force = 0;

  // Standard range is set to short range

  nNxtButtonTask  = -2;

  eraseDisplay();

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Force");
  nxtDisplayCenteredTextLine(3, "Test 1");
  wait1Msec(2000);
  eraseDisplay();

  while(true) {
    // Read the sensor value
    _force = HTFreadSensor(HTFORCE);

    nxtDisplayClearTextLine(3);
    nxtDisplayClearTextLine(4);
    nxtDisplayTextLine(3, "Force:  %4d", _force);
    wait1Msec(50);
  }
}

/*
 * $Id: hitechnic-force-test1.c 123 2012-11-02 16:35:15Z xander $
 */
