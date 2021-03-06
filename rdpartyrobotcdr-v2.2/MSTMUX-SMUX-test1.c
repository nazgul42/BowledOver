#pragma config(Sensor, S1,     HTSMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: MSTMUX-SMUX-test1.c 48 2011-02-13 20:35:38Z xander $
 */

/**
 * MSTMUX-driver.h provides an API for the Mindsensors Touch Sensor MUX.  This program
 * demonstrates how to use that API in combination with a HiTechnic Sensor MUX.
 *
 * The author of this program cannot be held responsible for the effects of this unholy
 * union.  Loss of life due to universal existance failure or accidentally created
 * wormholes may occur.  You have been warned.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors and HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 24-May-2010
 * version 0.1
 */

#include "drivers/HTSMUX-driver.h"
#include "drivers/MSTMUX-driver.h"

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor MSTMUX = msensor_S1_1;

task main () {
  nxtDisplayCenteredTextLine(0, "Mindsensors");
  nxtDisplayCenteredBigTextLine(1, "TMUX");
  nxtDisplayCenteredTextLine(3, "SMUX Test");
  nxtDisplayCenteredTextLine(5, "Connect SMUX to");
  nxtDisplayCenteredTextLine(6, "S1 and TMUX to");
  nxtDisplayCenteredTextLine(7, "SMUX Port 1");
  wait1Msec(2000);

  while (true) {
    eraseDisplay();
    nxtDisplayTextLine(0, "MS Touch MUX");

    // Get the raw data from the sensor, this is not processed
    // by the driver in any way.
    nxtDisplayTextLine(1, "Raw: %d", 1023 - HTSMUXreadAnalogue(MSTMUX));

    // Go through each possible touch switch attached to the TMUX
    // and display whether or not is active (pressed)
    for (int i = 1; i < 4; i++) {
      if (MSTMUXisActive(MSTMUX, i))
        nxtDisplayTextLine(i+2, "Touch %d: on", i);
      else
        nxtDisplayTextLine(i+2, "Touch %d: off", i);
    }

    // Display the binary value of the active touch switches
    // 0 = no touch, 1 = touch 1 active, 2 = touch 2 active, etc.
    // touch 1 + touch 2 active = 1 + 2 = 3.
    nxtDisplayTextLine(7, "Status: %d", MSTMUXgetActive(MSTMUX));
    wait1Msec(50);
  }
}

/*
 * $Id: MSTMUX-SMUX-test1.c 48 2011-02-13 20:35:38Z xander $
 */
