#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  jumper1,        sensorTouch)
#pragma config(Sensor, dgtl2,  jumper2,        sensorTouch)
#pragma config(Sensor, dgtl3,  urf,            sensorSONAR_cm)
#pragma config(Sensor, dgtl8,  led_sred,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl9,  led_red,        sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, led_syellow,    sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, led_yellow,     sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           flipper,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           sw_motor,      tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,           nw_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           shooter_right, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           shooter_left,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           se_motor,      tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port7,           ne_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           backup_intake, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           intake,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

const int defspeed = 127;
const float rotation = 627.2;
const float remnant = 344;
const float cell = 2;
const float turnticks = 390;

const int highflag = 85;
const int medflag = 50;

void pre_auton() {
	bStopTasksBetweenModes = true;
}

void go(float rotations) {
	resetMotorEncoder(sw_motor);
	resetMotorEncoder(se_motor);

	int speed;
	float ticks = (rotations * rotation) - remnant;
	if (rotations < 0) {
		speed = defspeed * -1;
	} else {
		speed = defspeed;
	}

	if (ticks > 0){
		while ((getMotorEncoder(sw_motor) <= ticks) && (getMotorEncoder(se_motor) >= -1*ticks)) {
			motor[nw_motor] = speed;
			motor[sw_motor] = speed;
			motor[ne_motor] = -1 * speed;
			motor[se_motor] = -1 * speed;
		}
	} else {
		while ((getMotorEncoder(sw_motor) >= ticks) && (getMotorEncoder(se_motor) <= -1*ticks)) {
			motor[nw_motor] = speed;
			motor[sw_motor] = speed;
			motor[ne_motor] = -1 * speed;
			motor[se_motor] = -1 * speed;
		}
	}
	motor[nw_motor] = 0;
	motor[ne_motor] = 0;
	motor[sw_motor] = 0;
	motor[se_motor] = 0;
}

void turnLeft(float turns) {
	resetMotorEncoder(sw_motor);
	resetMotorEncoder(se_motor);

	float ticks = turns * turnticks;

	while ((getMotorEncoder(sw_motor) >= -1*ticks) || (getMotorEncoder(se_motor) >= -1*ticks)) {
		motor[nw_motor] = -1 * defspeed;
		motor[sw_motor] = -1 * defspeed;
		motor[ne_motor] = -1 * defspeed;
		motor[se_motor] = -1 * defspeed;
	}
	motor[nw_motor] = 0;
	motor[ne_motor] = 0;
	motor[sw_motor] = 0;
	motor[se_motor] = 0;
}

void turnRight(int turns) {
	resetMotorEncoder(sw_motor);
	resetMotorEncoder(se_motor);

	float ticks = turns * turnticks;

	while ((getMotorEncoder(sw_motor) <= ticks) || (getMotorEncoder(se_motor) <= ticks)) {
		motor[nw_motor] = defspeed;
		motor[sw_motor] = defspeed;
		motor[ne_motor] = defspeed;
		motor[se_motor] = defspeed;
	}
	motor[nw_motor] = 0;
	motor[ne_motor] = 0;
	motor[sw_motor] = 0;
	motor[se_motor] = 0;
}

void intakeop(int speed) {
	motor[intake] = speed;
}

void shooterop(int speed) {
	motor[shooter_left] = -1 * speed;
	motor[shooter_right] = speed;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

/*
RED TEAM, FLAG SIDE: JUMPER 1
BLUE TEAM, FLAG SIDE: JUMPER 2
If not on flag side, do not plug in jumper!!
*/

task autonomous() {
	if (SensorValue[jumper1] == 1) {
		go(1.6 * cell);
		intakeop(-127);
		delay(300);
		go(-1.2 * cell);
		intakeop(0);
		turnLeft(1);
		go(0.6 * cell);
		shooterop(127);
		delay(3300);
		shooterop(0);
		intakeop(-127);
		go(0.47 * cell);
		delay(1000);
		shooterop(127);
		delay(3300);
		shooterop(0);
		go(0.8* cell);
		intakeop(0);
	} else if (SensorValue[jumper2] == 1) {
		go(1.6 * cell);
		intakeop(-127);
		delay(300);
		go(-1.2 * cell);
		intakeop(0);
		turnRight(1);
		go(0.6 * cell);
		shooterop(127);
		delay(3300);
		shooterop(0);
		intakeop(-127);
		go(0.47 * cell);
		delay(1000);
		shooterop(127);
		delay(3300);
		shooterop(0);
		go(0.8* cell);
		intakeop(0);
	}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task flashLED() {
	turnLEDOn(led_red);
	delay(500);
	turnLEDOff(led_red);
	turnLEDOn(led_yellow);
	delay(500);
	turnLEDOff(led_yellow);
}

task usercontrol() {
	while (true) {
		// drive train
		motor[nw_motor] = vexRT[Ch3];
		motor[sw_motor] = vexRT[Ch3];

		motor[ne_motor]= -1 * vexRT[Ch2];
		motor[se_motor] = -1 * vexRT[Ch2];

		// flag detector
		if (medflag <= SensorValue[urf] && SensorValue[urf] <= medflag + 10) {
			turnLEDOn(led_yellow);
			turnLEDOn(led_syellow);
			turnLEDOff(led_red);
			turnLEDOff(led_sred);
		} else if (highflag <= SensorValue[urf] && SensorValue[urf] <= highflag + 10) {
			turnLEDOff(led_yellow);
			turnLEDOff(led_syellow);
			turnLEDOn(led_red);
			turnLEDOn(led_sred);
		} else {
			turnLEDOff(led_yellow);
			turnLEDOff(led_syellow);
			turnLEDOff(led_red);
			turnLEDOff(led_sred);
		}

		// shooter control
		if (limitSwitch == 0) {
			motor[shooter_left] = -127;
			motor[shooter_right] = 127;
		} else {
			motor[shooter_left] = 0;
			motor[shooter_right] = 0;
		}

		if (vexRT[Btn5U] == 1) {
			motor[shooter_left] = -127;
			motor[shooter_right] = 127;
		}

		// intake control
		if (vexRT[Btn6D] == 1) {
			motor[intake] = 127;
		} else if (vexRT[Btn6U] == 1){
			motor[intake] = -127;
		} else {
			motor[intake] = 0;
		}

		// flipper control
		if (vexRT[Btn8L] == 1) {
			motor[flipper] = -127;
		} else if (vexRT[Btn8D]){
			motor[flipper] = 127;
		} else {
			motor[flipper] = 0;
		}

		// led control
		if (vexRT[Btn7L] == 1) {
			startTask(flashLED);
		}
	}
}
