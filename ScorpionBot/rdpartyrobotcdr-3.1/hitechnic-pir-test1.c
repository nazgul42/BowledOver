#pragma config(Sensor, S1,     HTPIR,                sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-pir-test1.c 123 2012-11-02 16:35:15Z xander $
 */

/**
 * hitechnic-pir.h provides an API for the HiTechnic PIR Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 26 August 2012
 * version 0.1
 */

#include "drivers/hitechnic-pir.h"

// Draw a little stick figure
void drawStickFigure(int offset)
{
  nxtEraseRect(0, 0, 99, 50);
  nxtDrawCircle(offset + 43, 40, 15);
  nxtDrawLine(offset + 50,25,offset + 50,10);
  nxtDrawLine(offset + 43, 22, offset + 58, 22);
  nxtDrawLine(offset + 43, 0, offset + 50, 10);
  nxtDrawLine(offset + 50, 10, offset + 58, 0);
}

task main () {
  int reading = 0;
  int x = 0;
  int deadband = HTPIR_DEFAULT_DEADBAND;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "PIR");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(6, "L/ENTER/R");
  nxtDisplayCenteredTextLine(7, "change deadband");

  wait1Msec(2000);
  eraseDisplay();

  while(true) {
    if (nNxtButtonPressed != kNoButton)
    {
      switch (nNxtButtonPressed)
      {
        case kRightButton: deadband++; break;
        case kLeftButton:  deadband--; break;
        case kEnterButton: deadband = HTPIR_DEFAULT_DEADBAND; break;
      }

      // Make sure the value stays between 0 and 47
      deadband = clip(deadband, 0, 47);

      // Debounce
      while (nNxtButtonPressed != kNoButton) EndTimeSlice();

      // Set the new dead band value.
      HTPIRsetDeadband(HTPIR, deadband);
    }

    // Get the IR levels from the PIR sensor
    reading = HTPIRreadSensor(HTPIR);
    nxtDisplayTextLine(0, "HT PIR %d / %d", deadband, reading);

    // Draw a cool little stick figure
    x = (40 * reading) / 100;
    drawStickFigure(x);
    wait1Msec(50);

  }
}

/*
 * $Id: hitechnic-pir-test1.c 123 2012-11-02 16:35:15Z xander $
 */
