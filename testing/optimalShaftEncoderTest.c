#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    potentiometer,  sensorPotentiometer)
#pragma config(Sensor, dgtl3,  urf,            sensorSONAR_cm)
#pragma config(Sensor, dgtl5,  encoderOne,     sensorQuadEncoder)
#pragma config(Sensor, dgtl10, led_red,        sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, led_yellow,     sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, led_green,      sensorLEDtoVCC)
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

/*
== BUTTON LAYOUT ==
RIGHT & LEFT JOYSTICKS -> drive train (right side & left side)
5U -> plunger control
6U -> Intake Up
6D -> Intake Down
7L -> Flash LEDs
*/

const int highflag = 95;
const int medflag = 55;
//bool released = false;

//task resetOpticalEncoder() {
//	while (true) {
//		if (vexRT[Btn5U] == 1) {
//			SensorValue[encoderOne] = 0;
//			delay(1000);
//		}
//		if (vexRT[Btn5U] == 1) {
//			button_state = 1;
//		}
//		if (vexRT[Btn5U] == 0) {
//			if (button_state == 1) {
//				released = true;
//			}
//			button_state = 0;
//		}
//	}
//}

task flashLED() {
	turnLEDOn(led_red);
	delay(500);
	turnLEDOff(led_red);
	turnLEDOn(led_yellow);
	delay(500);
	turnLEDOff(led_yellow);
	turnLEDOn(led_green);
	delay(500);
	turnLEDOff(led_green);
}

task main() {
	int value;
	bool canPressButton = true;
	SensorValue[encoderOne] = 0;
	//startTask(resetOpticalEncoder);
	while(true){
		//value = SensorValue[encoderOne];
		//writeDebugStreamLine("%d", value);
		// drive train
		motor[nw_motor] = vexRT[Ch3];
		motor[sw_motor] = vexRT[Ch3];

		motor[ne_motor]= -1 * vexRT[Ch2];
		motor[se_motor] = -1 * vexRT[Ch2];

		// flag detector9
		if (vexRT[Btn8D] == 1) {
			if (medflag <= SensorValue[urf] <= medflag + 5) {
				turnLEDOn(led_yellow);
				} else if (highflag <= SensorValue[urf] <= highflag + 5) {
				turnLEDOn(led_green);
				} else {
				turnLEDOn(led_red);
			}
			} else {
			turnLEDOff(led_red);
			turnLEDOff(led_yellow);
			turnLEDOff(led_green);
		}

		// shooter control
		//-259

		if (vexRT[Btn5U] == 1) {
			motor[shooter_left] = -127;
			motor[shooter_right] = 127;
		}
		else {
			motor[shooter_left] = 0;
			motor[shooter_right] = 0;
		}
		if (SensorValue[encoderOne] < 259 && SensorValue[encoderOne] > 1) {
			motor[shooter_left] = -127;
			motor[shooter_right] = 127;
		}
		else if (SensorValue[encoderOne] > 259) {
			motor[shooter_left] = 0;
			motor[shooter_right] = 0;
			SensorValue[encoderOne] = 0;
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
