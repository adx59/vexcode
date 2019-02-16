
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl3,  urf,            sensorSONAR_cm)
#pragma config(Sensor, dgtl5,  encoderOne,     sensorQuadEncoder)
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

//This is Jeremy's Competition Template code in order to not mess up the other Competition Template.
//This is for the far side auton and can be deleted afterwards however if the far side autons and close side autons
//work on this doc, then we will copy this o`ver onto the original file

/* */


/**
* LCD AutonSelect starts here.
*/

// 0 = don't run auton
// 1 = flag-side red
// 2 = flag-side blue
// 3 = far-side red
// 4 = far-side blue
int auton = 0;

int onOption = 0;
string menuOptions[5] = {
	"No Auton",
	"Flag-Side Red",
	"Flag-Side Blue",
	"Far-Side Red",
	"Far-Side Blue"
};

task renderLCD() {
	while (true) {
		displayLCDCenteredString(0, menuOptions[onOption]);
		if (auton != onOption) {
			displayLCDString(1, 0, " <     []     > ");
			} else {
			displayLCDString(1, 0, " <     {}     > ");
		}
	}
}

task watchButtons() {
	bool pressed = false;
	while (true) {
		if (nLCDButtons != 0 && !pressed) {
			if (nLCDButtons == 1) {
				if (onOption > 0) {
					onOption--;
				}
				}	else if (nLCDButtons == 2) {
				auton = onOption;
				} else if (nLCDButtons == 4) {
				if (onOption < 4) {
					onOption++;
				}
			}
			pressed = true;
		}
		if (nLCDButtons == 0) {
			pressed = false;
		}
	}
}

/**
* LCD AutonSelect ends here.
*/

const int defspeed = 100;
const float rotation = 627.2;
const float remnant = 344;
const float cell = 2;
const float turnticks = 350;

const int highflag = 85;
const int medflag = 50;

void pre_auton() {
	bStopTasksBetweenModes = true;

	bLCDBacklight = true;
	startTask(watchButtons);
	startTask(renderLCD);
}

/**
* Runs the robot forward, but allows you to specify speed per side.
*
* @param {float} rotations Number of rotations to go.
* @param {int} lspd Speed for left side to go.
* @param {int} rspd Speed for right side to go.
*/
void sgo(float rotations, int lspd, int rspd) {
	resetMotorEncoder(sw_motor);
	resetMotorEncoder(se_motor);

	float ticks = (rotations * rotation) - remnant;

	if (ticks > 0){
		while ((getMotorEncoder(sw_motor) <= ticks) && (getMotorEncoder(se_motor) >= -1*ticks)) {
			motor[nw_motor] = lspd;
			motor[sw_motor] = lspd;
			motor[ne_motor] = -1 * rspd;
			motor[se_motor] = -1 * rspd;
		}
		} else {
		while ((getMotorEncoder(sw_motor) >= ticks) && (getMotorEncoder(se_motor) <= -1*ticks)) {
			motor[nw_motor] = lspd;
			motor[sw_motor] = lspd;
			motor[ne_motor] = -1 * rspd;
			motor[se_motor] = -1 * rspd;
		}
	}
	motor[nw_motor] = 0;
	motor[ne_motor] = 0;
	motor[sw_motor] = 0;
	motor[se_motor] = 0;
}

/**
* Runs the robot forward.
*
* @param {float} rotations Number of rotations to run.
*/
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

/**
* Turn the robot counter-clockwise.
*
* @param {float} turns Degrees to turn, in increments of 90 degrees.
*/
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

/**
* Turn the robot clockwise.
*
* @param {float} turns Degrees to turn, in increments of 90 degrees.
*/
void turnRight(float turns) {
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

/**
* Sets the intake speed.
*
* @param {int} speed Speed to run the intake at.
*/
void intakeop(int speed) {
	motor[intake] = speed;
}

/**
* Sets the shooter speed.
*
* @param {int} speed Speed to run the shooter at.
*/
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

task autonomous() {
	if (auton == 1) {
		go(1.6 * cell);
		intakeop(-127);
		delay(500);
		go(-1.2 * cell);
		intakeop(0);
		turnLeft(1.11);
		go(0.45 * cell);
		shooterop(127);
		delay(3500);
		shooterop(0);
		intakeop(-127);
		go(0.6 * cell);
		delay(1000);
		shooterop(127);
		delay(3500);
		shooterop(0);
		go(-0.1 * cell);
		sgo(1* cell, 47, 127);
		delay(2000);
		intakeop(0);
		} else if (auton == 2) {
		go(1.6 * cell);
		intakeop(-127);
		delay(500);
		go(-1.05 * cell);
		intakeop(0);
		turnRight(1.115);
		go(0.49 * cell);
		shooterop(127);
		delay(3500);
		shooterop(0);
		intakeop(-127);
		go(0.6 * cell);
		delay(1000);
		shooterop(127);
		delay(3500);
		shooterop(0);
		go(-0.15 * cell);
		sgo(1* cell, 127, 47);
		delay(1700);
		go(0.1 * cell);
		delay(500);
		intakeop(0);
		} else if (auton == 3) {
		go(1.8 * cell);
		intakeop(-127);
		delay(500);
		intakeop(0);
		go(-0.06 * cell);
		turnRight(0.95);
		go(-0.927 * cell);
		} else if (auton == 4) {
		go(1.8 * cell);
		intakeop(-127);
		delay(500);
		intakeop(0);
		go(-0.06 * cell);
		turnLeft(0.95);
		go(-0.927 * cell);
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

task usercontrol() {
	while (true) {
		// drive train
		motor[nw_motor] = vexRT[Ch3];
		motor[sw_motor] = vexRT[Ch3];

		motor[ne_motor]= -1 * vexRT[Ch2];
		motor[se_motor] = -1 * vexRT[Ch2];

		// shooter control
		if (vexRT[Btn5U] == 1) {
			motor[shooter_left] = -127;
			motor[shooter_right] = 127;
			} else {
			motor[shooter_left] = 0;
			motor[shooter_right] = 0;
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
	}
}
