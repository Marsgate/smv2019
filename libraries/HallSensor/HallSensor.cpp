#include "Arduino.h"
#include "HallSensor.h"

void HallSensor::setup(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

int HallSensor::pull(){
	if(digitalRead(_pin))
		return 0;
	else
		return 1;
}

HallSensorController::HallSensorController(int pin1, int pin2, int pin3){
	_h1.setup(pin1);
	_h2.setup(pin2);
	_h3.setup(pin3);
}

int HallSensorController::pull(){
	int flags = _h1.pull() | _h2.pull() << 1 | _h3.pull() << 2;
	//Serial.println(flags, BIN);
    return flags;
}

int HallSensorController::getRotation(){
	int arraySize = 6;
	int order[arraySize] = {4,6,2,3,1,5};
	int flags = pull();
	int index = -1;
	for (int i=0; i<arraySize; i++) {
		if (flags == order[i]) {
			index = i;
			break;
		}
	}
	return index;
}
