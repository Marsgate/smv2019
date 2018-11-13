#include <Coil.h>
#include <HallSensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

/*********************************/
//library configuration and object creation

//lcd setup
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//hall sensor setup (pin1, pin2, pin3)
HallSensorController hall(A2, A1, A3);

// Coil setup (positive, negative, offset)
Coil a(11, 10, 0);
Coil b(9, 6, 2);
Coil c(5, 3, 4);


/*********************************/
//coil control functions
void coilSet(int motorSpeed){
  a.motorSpeed = motorSpeed;
  b.motorSpeed = motorSpeed;
  c.motorSpeed = motorSpeed;
}

void coilUpdate(int rotation){
  a.update(rotation);
  b.update(rotation);
  c.update(rotation);
}

/*********************************/
//interrupt function
void hallISR(){
  int rotation = hall.getRotation();
  coilUpdate(rotation);
}

/*********************************/
//main setup and loop

void setup(){
  Serial.begin(9600);

  //lcd init
  lcd.begin(16, 2);

  a.set(0);
  b.set(0);
  c.set(0);
}

void loop(){
  int coilSpeed = getThrottle();

  
}
