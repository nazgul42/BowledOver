#pragma config(Hubs,  S3, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S3_C1_1,     shoulder,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C1_2,     elbow,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C1_1,     motorNorth,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C1_2,     motorEast,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C2_1,     motorWest,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C2_2,     motorSouth,    tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S4_C3_1,     motorJ,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S4_C3_2,     wrist,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C4_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Values in inches. See drawings in engineer's notebook for details.
const float a = 15.3;
const float b = 15.3;
const float shoulderHeight = 14.6;

float startX = 9;
float startY = 18.5;

float targetX = startX;
float targetY = startY;
float lastX, lastY;

int wristNudge = 0;

bool shouldPowerWrist = true;

const float H_TIER_1 = 19.34;
const float X_TIER_1 = 9;
const float H_TIER_2_UPPER = 31.619987;
const float X_TIER_2_UPPER = 2.76;
const float H_TIER_2 = 36.26;
const float X_TIER_2 = -0.279996;
const float H_TIER_3 = 45.059975;
const float X_TIER_3 = -.279996;

const float H_DISPENSER = 5.86;
const float X_DISPENSER = 17.76;

struct
{
  int powerMax;
  int direction;
  float degreesPerEncoder;
  float degreesAtZero;
  int closeEnough;

  // PID variables
  float Kp, Kd, Ki;
  float integral;
  float difference;

  int lastEncoderValue;
  double lastEncoderTime;
} Joint;

Joint jShoulder;
Joint jElbow;
Joint jWrist;

void moveToXY(float x, float y)
{
	if (y < 4)
		y = 4;
	//writeDebugStreamLine("%f,%f",x,y);
	lastX = targetX;
	lastY = targetY;
	targetX = x;
	targetY = y;

	jShoulder.lastEncoderValue = -1;
	jElbow.lastEncoderValue = -1;
}

float degreesToEncoder(Joint joint, float degrees)
{
	return (degrees - joint.degreesAtZero) / joint.degreesPerEncoder;
}

float encoderToDegrees(Joint joint, float encoder)
{
	return encoder * joint.degreesPerEncoder + joint.degreesAtZero;
}

void initEncoders()
{
	nMotorEncoder[shoulder] = 0;
	nMotorEncoder[elbow] = 0;
	nMotorEncoder[wrist] = 0;
	wait1Msec(300);
}

void init()
{
	jShoulder.powerMax = 90;
	jShoulder.direction = -1;
	jShoulder.degreesPerEncoder = .00983; //.0101221;
	jShoulder.degreesAtZero = 307.63; //308.44555;
	jShoulder.closeEnough = 70;
	jShoulder.Kp = .019;
	jShoulder.Ki = .015;
	jShoulder.Kd = .0;
	jShoulder.difference = 0;
	jShoulder.integral = 0;
	jShoulder.lastEncoderValue = -1;

	jElbow.powerMax = 90;
	jElbow.direction = 1;
	jElbow.degreesPerEncoder = -.0351;//-.030213;
	jElbow.degreesAtZero = -21.787;//8.3734;
	jElbow.closeEnough = 70;
	jElbow.Kp = .021;
	jElbow.Ki = .009;
	jElbow.Kd = 0;
	jElbow.difference = 0;
	jElbow.integral = 0;
	jElbow.lastEncoderValue = -1;

	jWrist.powerMax = 70;
	jWrist.direction = 1;
	jWrist.degreesPerEncoder = -.1309;
	jWrist.degreesAtZero = -1.078;
	jWrist.closeEnough = 25;
	jWrist.Kp = .29;
	jWrist.Ki = .08;
	jWrist.Kd = 0;
	jWrist.difference = 0;
	jWrist.integral = 0;
	jWrist.lastEncoderValue = -1;
}

int powerForJoint(Joint joint, int encoderValue, int targetEncoder)
{
	if (abs(encoderValue - targetEncoder) <= joint.closeEnough)
	{
		return 0;
	}

	if (encoderValue != joint.lastEncoderValue)
	{
		joint.lastEncoderValue = encoderValue;
		joint.lastEncoderTime = nPgmTime;
	}

	int error = targetEncoder - encoderValue;
	float proportional = error*joint.Kp;

	joint.integral += error;
	joint.integral *= joint.Ki;

	int rateOfChange = error-joint.difference;
	float derivitive = rateOfChange*joint.Kd;
	joint.difference = error;

	int power = proportional + joint.integral + derivitive;

	if (power > joint.powerMax)
		power = joint.powerMax;
	else if (power < -joint.powerMax)
		power = -joint.powerMax;
	power *= joint.direction;
	return power;
}

// Returns true if motors are done moving

bool setMotorPowersForXY()
{
	bool motorsDoneMoving = true;

	float theta = PI/2 + atan2(targetY-shoulderHeight,targetX);
	float c = sqrt(pow(targetY-shoulderHeight,2)+pow(targetX,2));
	if (c >= a+b)
	{
		targetX = lastX;
		targetY = lastY;
		return true;
	}
	float angleC = acos( (pow(c,2)-pow(b,2)-pow(a,2)) / (-2*a*b) );
	float angleA = asin( (a * sin(angleC) / c) );

	int shoulderTarget = (int)degreesToEncoder(jShoulder, (angleA + theta) * 180 / PI);
	int elbowTarget = (int)degreesToEncoder(jElbow, angleC * 180 / PI) + 7;

	if (shoulderTarget > 0)
		shoulderTarget = 0;
	if (elbowTarget > 0)
		elbowTarget = 0;

	motor[shoulder] = -powerForJoint(jShoulder, nMotorEncoder[shoulder], shoulderTarget);
	motor[elbow] = powerForJoint(jElbow, nMotorEncoder[elbow], elbowTarget);

	if (abs(nMotorEncoder[shoulder] - shoulderTarget) > jShoulder.closeEnough ||
		  abs(nMotorEncoder[elbow]    - elbowTarget)    > jElbow.closeEnough)
		motorsDoneMoving = false;

	if ((nPgmTime - jShoulder.lastEncoderTime) > 300 && (nPgmTime - jWrist.lastEncoderTime) > 300)
		motorsDoneMoving = true;

	float shoulderAngle = encoderToDegrees(jShoulder, nMotorEncoder[shoulder]);
	float elbowAngle = encoderToDegrees(jElbow, nMotorEncoder[elbow]);
	float targetWristAngle = shoulderAngle + elbowAngle - 180 + wristNudge;
	int wristTarget = degreesToEncoder(jWrist, targetWristAngle);
	nxtDisplayTextLine(0,"<shoulder: %f",shoulderAngle);
	nxtDisplayTextLine(3,"<elbow:    %f",elbowAngle);
	if (shouldPowerWrist)
	{
		int wristPower = powerForJoint(jWrist, nMotorEncoder[wrist], wristTarget);
		motor[wrist] = wristPower;
	}

	nxtDisplayTextLine(1,"targetX: %f",targetX);
	nxtDisplayTextLine(2,"targetY: %f",targetY);

	return motorsDoneMoving;
}
