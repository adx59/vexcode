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

// one rotation = 40.8 cm
// one cell = 60.5 cm
// rot / cell = 1.482 rots.
// wheel rad = 6.5 cm
// ticks per rotation = 627.2
// therefore 1 cell = 929.51 ticks

// calibrate variables below
float tickspercell = 929.51;

float timepercell = 650; // time to traverse one cell on the field
float timeperhalfturn = 550; // time to turn 45 degrees
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
	resetMotorEncoder(sw_motor);
	motor[ne_motor] = -1 * speed;
	motor[se_motor] = -1 * speed;
	motor[nw_motor]= speed;
	motor[sw_motor] = speed;
	while (getMotorEncoder(sw_motor) < tickspercell*cells) {
		delay(10);
	}
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
		go(1);
		turnRight(2);
		liftop(127);
		delay(200);
		liftop(0);
		go(2.5);
	} else if (SensorValue[jumper2] == 1){
		go(1);
		turnLeft(2);
		liftop(127);
		delay(200);
		liftop(0);
		go(2.5);
	} else if (SensorValue[jumper3] == 1){
		go(1);
		turnLeft(2);
		liftop(127);
		delay(200);
		liftop(0);
		go(2.5);
	} else if (SensorValue[jumper4] == 1){
		go(1);
		turnRight(2);
		liftop(127);
		delay(200);
		liftop(0);
		go(2.5);
	} else if (SensorValue[jumper5] == 1){
		go(1);
	}
}
