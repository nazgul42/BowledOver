#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
  while (true)
  {
    getJoystickSettings(joystick);

    int lDrivePower = 0;
    int rDrivePower = 0;

    if (abs(joystick.joy1_y1) > 20)
      lDrivePower = joystick.joy1_y1*100/128;
    if (abs(joystick.joy1_y2) > 20)
      rDrivePower = joystick.joy1_y2*100/128;

      motor[rightDrive] = rDrivePower;
      motor[leftDrive] = -lDrivePower;
  }
}
