#pragma config(Sensor, S1,     HTPB,                sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-protoboard-exp2.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * hitechnic-protoboard.h provides an API for the HiTechnic Protoboard.  This is program 2
 * for the HTPB experimenter's kit.
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
 * 07 May 2010
 * version 0.1
 */

#include "drivers/hitechnic-protoboard.h"

task main() {
  // Local variables
  int inputdata;
  ubyte outputdata;

  // The data to be written: 0x3F = 111111 binary,
  // makes all digital ports outputs.
  HTPBsetupIO(HTPB, 0x3F);

  while(true) {
    // Read a 10bit wide analogue value from A0
    inputdata = HTPBreadADC(HTPB, 0, 10);

    eraseDisplay();
    nxtDisplayTextLine(1, "%d", inputdata);

    // Depending on the input voltage on A0,
    // turn on the corresponding LED.
    outputdata = 0x01;
    if (inputdata >  31) outputdata = 0x02;
    if (inputdata >  63) outputdata = 0x04;
    if (inputdata > 127) outputdata = 0x08;
    if (inputdata > 255) outputdata = 0x10;
    if (inputdata > 511) outputdata = 0x20;

    HTPBwriteIO(HTPB, outputdata);
    wait1Msec(50);
  }
}

/*
 * $Id: hitechnic-protoboard-exp2.c 123 2012-11-02 16:35:15Z xander $
 */
