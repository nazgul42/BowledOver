#pragma config(Sensor, S1,     MSIMU,                sensorI2CCustomFastSkipStates)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-imu-test3.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * mindsensors-imu.h provides an API for the Mindsensors AbsoluteIMU Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 26 August 2012
 * version 0.1
 */

#include "drivers/mindsensors-imu.h"

task main(){

  int heading;
  int x_val, y_val, z_val;      // axis values

  nxtDisplayCenteredTextLine(0, "Mindsensors");
  nxtDisplayCenteredBigTextLine(1, "IMU");
  nxtDisplayCenteredTextLine(3, "Test 3");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);
  eraseDisplay();

  while (true){

		// Read the Compass
    heading = MSIMUreadHeading(MSIMU);

		nxtDisplayTextLine(1, "Heading: %d", heading);

		// Read the magnetic fields (they're used to calculate the heading)
		MSIMUreadMagneticFields(MSIMU, x_val, y_val, z_val);
    nxtDisplayTextLine(3, "Magnetic fields:");
		nxtDisplayTextLine(4, "X: %d", x_val);
		nxtDisplayTextLine(5, "Y: %d", y_val);
		nxtDisplayTextLine(6, "Z: %d", z_val);
		wait1Msec(50);
  }
}

/*
 * $Id: mindsensors-imu-test3.c 123 2012-11-02 16:35:15Z xander $
 */
