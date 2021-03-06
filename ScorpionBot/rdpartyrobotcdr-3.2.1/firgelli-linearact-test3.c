/*
 * $Id: firgelli-linearact-test3.c 127 2012-12-05 19:32:39Z xander $
 */

/**
 * firgelli-linearact.h provides an API for the Firgelli Linear Actuator.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * TODO:
 * - Add ramping support (being worked on, has a few bugs)
 *
 * Credits:
 * - Big thanks to Firgelli for providing me with a Linear Actuator to play with!
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.55 beta 2 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 15 february 2010
 * version 0.1
 */

#include "drivers/firgelli-linearact.h"

task main () {
  tMotor testMotor = motorA;

  PlaySound(soundBeepBeep);
  nxtDisplayBigTextLine(3, "Retract");
  FLACretractLA(testMotor, 100);
  wait1Msec(500);

  // This stops the motor, handy in case of emergencies
  FLACstopLA(motorA);
  while(!isDone(testMotor)) wait1Msec(50);
  wait1Msec(200);
  nMotorEncoder[testMotor] = 0;
  wait1Msec(1000);

  PlaySound(soundBeepBeep);
  eraseDisplay();
  nxtDisplayBigTextLine(1, "Extend");
  nxtDisplayTextLine(3, "ticks:  40");
  nxtDisplayTextLine(4, "speed:  50");
  FLACextendLA(testMotor, 50, 40);
  while(!isDone(testMotor)) wait1Msec(50);
  if (isStalled(testMotor))
    nxtDisplayTextLine(7, "STALLED");
  wait1Msec(1000);


  PlaySound(soundBeepBeep);
  eraseDisplay();
  nxtDisplayBigTextLine(1, "Done");
  wait1Msec(2000);
}

/*
 * $Id: firgelli-linearact-test3.c 127 2012-12-05 19:32:39Z xander $
 */
