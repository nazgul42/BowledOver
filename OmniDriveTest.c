#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Sensor, S2,     ,                    sensorI2CMuxController)
#pragma config(Sensor, S4,     ,                    sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     LiftMotor1,    tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     RightDrive,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     LiftMotor2,    tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     LeftDrive,     tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C2_1,     motorH,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C2_2,     motorI,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  while (true){motor[motorH] = 100;}
  wait10Msec(100);
  motor[motorH] = 0;
}
