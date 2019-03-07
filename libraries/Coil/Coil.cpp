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
	
	Serial.print(polarity);
	Serial.print(", ");
	analogWrite(_pos, 0);
	digitalWriteFast(_neg, 0);
	
	if(polarity == 1)
		analogWrite(_pos, motorSpeed);
	
	if(polarity == -1)
		digitalWriteFast(_neg, 1);
}

void Coil::update(int index){
	index += _offset;
	
	int posmap[6] = {1, 1, 0, -1, -1, 0};
	
	if(index > 5)
		index -= 6;
	
	set(posmap[index]);
}
