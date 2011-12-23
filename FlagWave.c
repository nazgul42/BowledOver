#pragma config(Hubs,  S1, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,                    sensorI2CMuxController)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_6,    flagServo,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
  while (true)
  {
    servo[flagServo] = 45;
    wait1Msec(500);
    servo[flagServo] = 135;
    wait1Msec(500);
  }
}