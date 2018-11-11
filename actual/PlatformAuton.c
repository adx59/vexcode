#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  jumper1,        sensorTouch)
#pragma config(Sensor, dgtl2,  jumper2,        sensorTouch)
#pragma config(Sensor, dgtl3,  jumper3,        sensorTouch)
#pragma config(Sensor, dgtl4,  jumper4,        sensorTouch)
#pragma config(Sensor, dgtl5,  jumper5,        sensorTouch)
#pragma config(Motor,  port2,           ne_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           se_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           lift_left,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           lift_right,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           nw_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           sw_motor,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           manipulator,   tmotorVex393_MC29, openLoop)

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

/*
BLUE TEAM, FAR SIDE: Jumper @ Digital Port 1
BLUE TEAM, CLOSE SIDE: Jumper @ Digital Port 2
RED TEAM, FAR SIDE: Jumper @ Digital Port 3
RED TEAM, CLOSE SIDE: Jumper @ Digital Port 4
*/


task main() {
	if (SensorValue[jumper1] == 1) {
		turnLeft(2);
		go(1);
		turnRight(2);
		go(2.5);
	} else if (SensorValue[jumper2] == 1){
		turnRight(2);
		go(1);
		turnLeft(2);
		go(2.5);
	} else if (SensorValue[jumper3] == 1){
		turnRight(2);
		go(1);
		turnLeft(2);
		go(2.5);
	} else if (SensorValue[jumper4] == 1){
		turnLeft(2);
		go(1);
		turnRight(2);
		go(2.5);
	} else if (SensorValue[jumper5] == 1){
		go(1); // go one cell forward
		turnLeft(2); // turn left 90 degrees
		turnRight(2); // turn right 90 degrees
		liftop(127); // operate lift to full speed
		manip(2); // manipulate 90 degrees
		liftop(-127); // operate lift in reverse
		delay(1000);
		liftop(0); // stop lift
	}
}