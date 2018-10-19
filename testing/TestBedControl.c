#pragma config(Sensor, in1,    light,          sensorReflection)
#pragma config(Sensor, in4,    potent,         sensorPotentiometer)
#pragma config(Sensor, in5,    potent2,        sensorPotentiometer)
#pragma config(Sensor, in7,    liner,          sensorLineFollower)
#pragma config(Sensor, dgtl11, button,         sensorTouch)
#pragma config(Sensor, dgtl12, touch,          sensorTouch)
#pragma config(Motor,  port1,           motoro,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           servo,         tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int speed = 95;

task main() {
	while (true) {
		motor[motoro] = speed;
		if (SensorValue[potent] >= 2000 && SensorValue[light] >= 500){
			startMotor(motoro, speed);
		}
		if (SensorValue[potent] < 2000 || SensorValue[light] < 500){
			stopMotor(motoro);
		}
		if (SensorValue[touch] == 1) {
			if (speed == 95){
				speed = -95;
			} else if (speed ==-95) {
				speed = 95;
			}
		}
	}
}