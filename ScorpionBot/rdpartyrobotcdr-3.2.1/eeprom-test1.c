#pragma config(Sensor, S1,     EEPROM,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: eeprom-test1.c 127 2012-12-05 19:32:39Z xander $
 */

/**
 * eeprom-driver.h provides an API for the AT24C512, 24AA512 and 24AA1025 EEPROMs.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Removed common.h include\n
 *        Removed array structs, replaced with typedefs
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.55 beta 2 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 20 February 2011
 * version 0.2
 */

#include "drivers/eeprom.h"

//tByteArray data;

task main () {
  string w_string = "MindstormsNXT";
  string r_string;
  tByteArray data;

  memcpy(data, w_string, sizeof(w_string));
  EEPROMwriteBytes(EEPROM, 0, data, 13);
  // After a write, you *must* wait 5 msec
  wait1Msec(5);

  eraseDisplay();
  memset(data, 0, sizeof(tByteArray));
  EEPROMreadBytes(EEPROM, 0, data, 13);
  // Make sure the string is 0 terminated.
  data[13] = 0;
  StringFromChars(r_string, &data[0]);

  nxtDisplayTextLine(1, "%s", r_string);
  wait1Msec(2000);
}

/*
 * $Id: eeprom-test1.c 127 2012-12-05 19:32:39Z xander $
 */
