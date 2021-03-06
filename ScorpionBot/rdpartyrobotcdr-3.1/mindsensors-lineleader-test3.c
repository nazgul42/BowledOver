#pragma config(Sensor, S1,     LLEADER,             sensorI2CCustom9V)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: mindsensors-lineleader-test3.c 123 2012-11-02 16:35:15Z xander $
 */

/** \file mindsensors-lineleader-test3.c
 * \brief Mindsensors LineLeader Sensor demo program
 *
 * mindsensors-lineleader-test3.c is a demo program for the Mindsensors LineLeader Sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: Reworked to use new driver API
 * - 0.3: More comments<br>
 *        Use clip() instead of manual clipping
 * - 0.4: Updated to use new array types that don't use structs\n
 *        Removed common.h from includes
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.54 AND HIGHER.
 * Xander Soldaat (xander_at_botbench.com)
 * 14 February 2011
 * version 0.4
 */

#define MSLL_I2C_ADDR 0x02

#include "drivers/mindsensors-lineleader.h"

#define printXY nxtDisplayStringAt
#define println nxtDisplayTextLine
#define clearln nxtDisplayClearTextLine

// The PID constants and base speed
#define DEFAULT_KP    5
#define DEFAULT_KI    0
#define DEFAULT_KD   30
#define DEFAULT_SP   50

// The file for the log data
#define LOGFILE   "linelead.dat"

#define MENUITEMS 5

// function prototypes
void doMainMenu();
void doMenuItem(int activeOption);
bool checkTimer(TTimers timer);
void doLineLead();
void writeParams();

string menuHeader;
string menuFooter;

const TTimers rightButtonTimer = T1;
const TTimers leftButtonTimer  = T2;
const TTimers enterButtonTimer = T3;

int activeOption = 0;

int keep_running = 0;

byte sensor = 0;

// array holding default values for PID constants and base speed
const int default_params[4] = {
                              DEFAULT_KP,
                              DEFAULT_KI,
                              DEFAULT_KD,
                              DEFAULT_SP };

// array to hold user entered values
int params[4];

const string optionMainMenu[5] = {
                              "Kp",
                              "Ki",
                              "Kd",
                              "Sp",
                              "Run" };

const string optionMainMenuFooter[5] = {
                              "Ent=Edit",
                              "Ent=Edit",
                              "Ent=Edit",
                              "Ent=Edit",
                              "Ent=Run" };

tByteArray signalstr;


// This function draws the current values of the sensor and other data on the screen
// in a visually pleasing way
task drawSensors() {
  while (keep_running == 1) {
    // This clears the entire area occupied by the small rectangles
    nxtEraseRect(6,62, 91, 43);
    for (int i = 0; i < 8; i++) {
      // Draw the rectangles for the signal strength first
      nxtDrawRect(6+(i*11),62, 14+(i*11), 50);
      nxtFillRect(6+(i*11),51+signalstr[i]/10, 14+(i*11), 50);
      // Draw a black rectangle if the sensor has detected the line,
      // a hollow one when nothing has been detected.
      if ((sensor >> i) & 1) {
        nxtFillRect(6+(i*11),48, 14+(i*11), 43);
      } else {
        nxtDrawRect(6+(i*11),48, 14+(i*11), 43);
      }
    }
    wait1Msec(100);
  }
}


// Keep the robot on the line!
task followTheYellowBrickRoad () {
  int powerA = 0;
  int powerC = 0;
  byte steering = 0;

  eraseDisplay();
  nxtDisplayCenteredTextLine(3, "Running...");
  nxtDisplayCenteredTextLine(5, "Press exit");
  nxtDisplayCenteredTextLine(6, "to stop");

  time1[T4] = 0;
  while (keep_running == 1) {
    steering = LLreadSteering(LLEADER);
    sensor = LLreadResult(LLEADER);
    LLreadSensorRaw(LLEADER, signalstr);

    powerA = (params[3] + steering);
    powerC = (params[3] - steering);

    // If your robot is going in the wrong direction, comment out the
    // lines above and uncomment the lines below.
    //powerA = (params[3] - steering);
    //powerC = (params[3] + steering);

    // this clips the values
    powerA = clip(powerA, -100, 100);
    powerC = clip(powerC, -100, 100);

    //if(powerA>100)  powerA=100;
    //if(powerA<-100) powerA=-100;
    //if(powerC<-100) powerC=-100;
    //if(powerC>100)  powerC=100;

    motor[motorA] = (byte)powerA;
    motor[motorC] = (byte)powerC;
		wait1Msec(1);
		if (sensor != 0xFF) {
		  time1[T4] = 0;
	  } else if (time1[T4] > 500) {
	    keep_running = 0;
	  }
  }

  motor[motorA] = 0;
  motor[motorC] = 0;
}

task redrawMenu() {
  while(true) {
    eraseDisplay();
    println(0, menuHeader);
    for (int i = 0; i < MENUITEMS; i++) {
      clearln(i + 1);
      if (i == activeOption) {
        if (i < 4)
          println(i + 1, "> %s [%3d] <", optionMainMenu[i], params[i]);
        else
          println(i + 1, "> %s      <", optionMainMenu[i]);
        println(7, menuFooter);
      } else {
        if (i < 4)
          println(i + 1, "  %s [%3d]", optionMainMenu[i], params[i]);
        else
          println(i + 1, "  %s", optionMainMenu[i]);
      }
    }
    wait1Msec(100);
  }
}

// Main task
task main () {

  // Set the default parameters and write them to the sensor
  memcpy(params, default_params, sizeof(default_params));
  writeParams();

  nNxtButtonTask  = -2;
  nNxtExitClicks = 3;

  StartTask(redrawMenu);
  doMainMenu();
  while(true)
    wait1Msec(100);
}

// Draw the main menu
void doMainMenu () {
  while (true) {
    menuHeader = "L/R to select";
    menuFooter = optionMainMenuFooter[activeOption];

    switch(nNxtButtonPressed) {
      case kRightButton:
            if (!checkTimer(rightButtonTimer)) {
              break;
            }
            if (activeOption == (MENUITEMS - 1))
              activeOption = 0;
            else
              activeOption++;
            menuFooter = optionMainMenuFooter[activeOption];
            wait1Msec(300);
            break;
      case kLeftButton:
            if (!checkTimer(leftButtonTimer)) {
              break;
            }
            if (activeOption == 0)
              activeOption = (MENUITEMS - 1);
            else
              activeOption--;
            menuFooter = optionMainMenuFooter[activeOption];
            wait1Msec(300);
            break;
      case kEnterButton:
            if (!checkTimer(rightButtonTimer)) {
              break;
            }
            wait1Msec(600);
            doMenuItem(activeOption);
            break;
      case kExitButton:
            wait1Msec(500);
            StopAllTasks();

    }
  }
}

// When enter is pressed in the doMainMenu() we come here.
// Here we handle the actual actions for each menu item.
void doMenuItem(int activeOption) {
  PlaySound(soundBlip);
  while(bSoundActive) EndTimeSlice();

  if (activeOption == 4) {
    doLineLead();
    return;
  }

  while (true) {
    menuHeader = "L/R to edit val";
    menuFooter = "Ent=Save/Exit=Def";
    switch(nNxtButtonPressed) {
      case kRightButton:
            if (!checkTimer(rightButtonTimer)) {
              break;
            }
            if (params[activeOption] < 128)
              params[activeOption]++;
            break;
      case kLeftButton:
            if (!checkTimer(leftButtonTimer)) {
              break;
            }
            if (params[activeOption] > 0)
              params[activeOption]--;
            break;
      case kEnterButton:
            if (!checkTimer(enterButtonTimer)) {
              break;
            }
            writeParams();
            wait1Msec(600);
            return;
            break;
      case kExitButton:
            params[activeOption] = default_params[activeOption];
            writeParams();
            wait1Msec(600);
            break;
    }
  }
}

// See if more than 300ms has elapsed
bool checkTimer(TTimers timer) {
  if (time1[timer] < 300) {
    return false;
  } else {
    time1[timer] = 0;
    return true;
  }
}

// Start and stop the line following task (followTheYellowBrickRoad)
void doLineLead() {
  sensor = 0;
  StopTask(redrawMenu);
  keep_running = 1;
  for (int i = 0; i < 5; i++) {
    PlaySound(soundBlip);
    wait1Msec(600);
  }
  PlaySound(soundFastUpwardTones);
  while(bSoundActive) EndTimeSlice();
  StartTask(drawSensors);
  StartTask(followTheYellowBrickRoad);
  while(nNxtButtonPressed != kExitButton && keep_running != 0) {
    wait1Msec(10);
  }
  // this will kill off the followTheYellowBrickRoad task
  keep_running = 0;
  wait1Msec(1000);
  StartTask(redrawMenu);
}

// Write the PID values to the LineLeader sensor
void writeParams() {
  LLsetKp(LLEADER, params[0], 32);
  LLsetKi(LLEADER, params[1], 32);
  LLsetKd(LLEADER, params[2], 32);
}

/*
 * $Id: mindsensors-lineleader-test3.c 123 2012-11-02 16:35:15Z xander $
 */
