/* 
 * HallSensor.h
 * A Library for interacting with 3 phase dc motor hall sensors 
 * Created by Micah C. Rassi, 2018
 */

#ifndef HALLSENSOR_H
#define HALLSENSOR_H

#include "Arduino.h"

class HallSensor{
	int _pin;
  public:
    void setup(int pin);
    int pull();     
};

class HallSensorController{
	HallSensor _h1;
	HallSensor _h2;
	HallSensor _h3;
	
	int pull();
	
  public:
    HallSensorController(int pin1, int pin2, int pin3);
	int getRotation();
};

#endif