/* 
 * Coil.h
 * A Library for controlling a 3 phase dc motor
 * Created by Micah C. Rassi, 2018
 */
 
#ifndef COIL_H_
#define COIL_H_

#include "Arduino.h"

class Coil{
    int _pos;
    int _neg;
	int _offset;
  public:
	int motorSpeed;
	Coil(int pos, int neg, int offset);
	void update(int rotation);
	void set(int polarity);
};

#endif
