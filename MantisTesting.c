#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     rSholder,      tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     rDrive,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C1_1,     lSholder,      tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     motorI,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     lDrive,        tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C2_2,     motorI,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    rFinger,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    lFinger,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    rWrist,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_4,    lWrist,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_5,    rElbow,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_6,    lElbow,               tServoContinuousRotation)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  servo[lFinger] = 0;
  while (true)
  {}
}
