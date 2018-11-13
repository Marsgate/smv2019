#include "Arduino.h"
#include "Coil.h"


Coil::Coil(int pos, int neg, int offset){
	pinMode(pos, OUTPUT);
	pinMode(neg, OUTPUT);
	_pos = pos;
	_neg = neg;
	_offset = offset;
}


void Coil::set(int polarity){
	
	
	digitalWrite(_pos, 1);
	digitalWrite(_neg, 0);
	
	if(polarity == 1)
		digitalWrite(_pos, 0);
		//analogWrite(_pos, 255 - motorSpeed);
	
	if(polarity == -1)
		digitalWrite(_neg, 1);
		//analogWrite(_neg, motorSpeed);
}

void Coil::update(int index){
	index += _offset;
	
	int posmap[6] = {1, 1, 0, -1, -1, 0};
	
	if(index > 5)
		index -= 6;
	
	set(posmap[index]);
}
