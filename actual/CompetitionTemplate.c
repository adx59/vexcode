#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  debugButt,      sensorTouch)
#pragma config(Sensor, dgtl2,  debugButt2,     sensorTouch)
#pragma config(Motor,  port2,           ne_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           se_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           lift_left,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           lift_right,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           nw_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           sw_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           manipulator,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           transmanip,    tmotorVex393_MC29, openLoop)

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

int controlMode = 1;

void startLift(int speed){
	startMotor(lift_left, speed*-1);
	startMotor(lift_right, speed);
}

void stopLift(){
	stopMotor(lift_left);
	stopMotor(lift_right);
}

// START AUTONOMOUS FUNCTIONS

int despeed = 127; // default speed

// calibrate variables below
float timepercell = 775; // time to traverse one cell on the field
float timeperhalfturn = 500; // time to turn 45 degrees
float timepermaniphturn = 750; // time for manipulator to turn 90 degrees

void turnLeft(int turns) {
	motor[ne_motor] = -1 * despeed;
	motor[se_motor] = -1 * despeed;
	motor[nw_motor]= -1 * despeed;
	motor[sw_motor] = -1 * despeed;
	delay(turns * timeperhalfturn);
	motor[ne_motor] = 0;
	motor[se_motor] = 0;
	motor[nw_motor]= 0;
	motor[sw_motor] = 0;
}

void turnRight(int turns) {
	motor[ne_motor] = despeed;
	motor[se_motor] = despeed;
	motor[nw_motor]= despeed;
	motor[sw_motor] = despeed;
	delay(turns * timeperhalfturn);
	motor[ne_motor] = 0;
	motor[se_motor] = 0;
	motor[nw_motor]= 0;
	motor[sw_motor] = 0;
}

void go(float cells){
	int speed;
	if (cells <= 0) {
		speed = despeed * -1; // change speed to negative if param passed is negative
	} else {
		speed = despeed;
	}
	motor[ne_motor] = -1 * speed;
	motor[se_motor] = -1 * speed;
	motor[nw_motor]= speed;
	motor[sw_motor] = speed;
	delay(cells * timepercell);
	motor[ne_motor] = 0;
	motor[se_motor] = 0;
	motor[nw_motor]= 0;
	motor[sw_motor] = 0;
}

void liftop(float speed) {
	motor[lift_left] = -1 * speed;
	motor[lift_right] = speed;
}

void manip(float turns){
	startMotor(manipulator, despeed);
	delay(turns * timepermaniphturn);
	stopMotor(manipulator);
}

void manipr(float turns) {
	startMotor(manipulator, -1*despeed);
	delay(turns * timepermaniphturn);
	stopMotor(manipulator);
}

void pre_auton() {
  bStopTasksBetweenModes = true;
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
	// no auton lul
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
    if (controlMode == 0) {
			motor[ne_motor] = -1 * (vexRT[Ch2] - vexRT[Ch1])/2;
			motor[se_motor] = -1 * (vexRT[Ch2] - vexRT[Ch1])/2;

			motor[nw_motor]= (vexRT[Ch2] + vexRT[Ch1])/2;
			motor[sw_motor] = (vexRT[Ch2] + vexRT[Ch1])/2;
		} else if (controlMode == 1) {
			motor[ne_motor] = -1 * vexRT[Ch2];
			motor[se_motor] = -1 * vexRT[Ch2];

			motor[nw_motor]= vexRT[Ch3];
			motor[sw_motor] = vexRT[Ch3];
		}

		if (vexRT[Btn6U] == 1 ){
			startLift(127);
		} else if (vexRT[Btn6D] ==  1) {
			startLift(-50);
		} else {
			stopLift();
		}


		if (vexRT[Btn5U] == 1) {
			startMotor(manipulator, 127);
		} else if (vexRT[Btn5D] == 1) {
			startMotor(manipulator, -127);
		} else {
			stopMotor(manipulator);
		}
  }
}
