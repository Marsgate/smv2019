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
//main setup and loop

void setup(){
  Serial.begin(9600);

  //lcd init
  lcd.begin(16, 2);
}

void loop(){
  int coilSpeed = 120;
  int rotation = hall.getRotation();
  coilUpdate(rotation);

  /*
  static unsigned long totalTime = 21 * 60000; //minutes * millis
  static unsigned long lastDisplayedTime;
  unsigned long timeRemainingMillis = totalTime - millis();
  
  if(timeRemainingMillis <= lastDisplayedTime - 1000){
    lcd.setCursor(2,0);
    lcd.print("     "); // five spaces to clear old time

    int minutes = timeRemainingMillis / 60000;
    int seconds  = timeRemainingMillis % minutes;
    lcd.setCursor(2,0);
    lcd.print(minutes);
    lcd.print(":");
    lcd.print(seconds);

    lastDisplayedTime = minutes*60000 + seconds*1000
  }
  */

  /* throttle
  //coil speed feedback
  static int lcs;
  if(coilSpeed != lcs){
    lcs = coilSpeed;
    lcd.clear();
    lcd.print("Speed ");
    lcd.print(lcs*100/255);
    lcd.print("%");
  }
  */
}


