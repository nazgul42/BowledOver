#pragma config(Sensor, S1,     LEGOEM,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * lego-energymeter.h provides an API for the Lego Energy Meter.  This program
 * demonstrates how to use that API to use the sensor in continuous mode.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits :
 * - Cosimano for sending me one of these.
 * - John Hansen for providing me with the specs.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 22 August 2010
 * version 0.1
 */

#include "drivers/lego-energymeter.h"

task main() {

  int _joule;
  float _voltageIn;
  float _currentIn;
  float _voltageOut;
  float _currentOut;
  float _wattIn;
  float _wattOut;

  nxtDisplayCenteredTextLine(0, "LEGO");
  nxtDisplayCenteredBigTextLine(1, "Energy");
  nxtDisplayCenteredTextLine(3, "Test 1");
  nxtDisplayCenteredTextLine(5, "Connect sensor");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);
  eraseDisplay();

	nxtDrawLine(0, 27, 99, 27);
	nxtDrawLine(0, 52, 99, 52);

  while (true) {
    //eraseDisplay();
    LEGOEMreadData(LEGOEM, _voltageIn, _currentIn, _voltageOut, _currentOut, _joule, _wattIn, _wattOut);
    nxtDisplayCenteredTextLine(0, "Energy Meter");
    nxtDisplayTextLine(2, "In:  %2.1fV|%2.3fA", _voltageIn, _currentIn);
    nxtDisplayTextLine(3, "Out: %2.1fV|%2.3fA", _voltageOut, _currentOut);
    nxtDisplayTextLine(5, "Pwr in:  %2.3fW", _wattIn);
    nxtDisplayTextLine(6, "Pwr out: %2.3fW", _wattOut);
    nxtDisplayTextLine(7, "Energy: %3dJ", _joule);
    wait1Msec(100);
  }
}
