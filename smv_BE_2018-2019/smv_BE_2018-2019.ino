#include <Coil.h>
#include <HallSensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <SPI.h>

/*********************************/
//Pin definitions
#define HALL1 24
#define HALL2 25
#define HALL3 26

#define EN_GATE 22
#define NFAULT 20
#define NOTCW 21

#define LED1 7
#define LED2 8

int lastTime = 0;

SPISettings spi_settings(160000, MSBFIRST, SPI_MODE1); 

/*********************************/
//library configuration and object creation

//lcd setup
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//hall sensor setup (pin1, pin2, pin3)
HallSensorController hall(HALL1, HALL2, HALL3);

// Coil setup (positive, negative, offset)
Coil a(30, 29, 0);
Coil b(2, 14, 2);
Coil c(6, 5, 4);

/*********************************/
//spi
int spiRead(){
  SPI.beginTransaction(spi_settings);
  int result = SPI.transfer(0);
  return result;
}

/*********************************/
//coil control functions
void coilSet(int motorSpeed){
  a.motorSpeed = motorSpeed;
  b.motorSpeed = motorSpeed;
  c.motorSpeed = motorSpeed;
}

void coilUpdate(int rotation){
  Serial.print("A:");
  a.update(rotation);
  Serial.print("B:");
  b.update(rotation);
  Serial.print("C:");
  c.update(rotation);
  Serial.println();
}

/*********************************/
//interrupt function
void hallISR(){
  int rotation = hall.getRotation();
  //Serial.println(rotation);
  coilUpdate(rotation);
}

/*********************************/
//main setup and loop

void setup(){
  delay(50);
  
  Serial.begin(9600);

  //pin mode setting
  pinMode(EN_GATE, OUTPUT);
  pinMode(NFAULT, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(NOTCW, INPUT);
  pinMode(LED2, OUTPUT);
  pinMode(SS, OUTPUT);
  

  //lcd init
  //lcd.begin(16, 2);

  //enable gate 
  digitalWrite(EN_GATE, HIGH);
  
  //start spi
  SPI.begin();
  
  

  a.set(0);
  b.set(0);
  c.set(0);

  /*
  attachInterrupt(HALL1, hallISR, CHANGE);
  attachInterrupt(HALL2, hallISR, CHANGE);
  attachInterrupt(HALL3, hallISR, CHANGE);
  */
}

void loop(){

  int curTime = millis();
  if(curTime - lastTime > 50){
    if(!digitalRead(NFAULT))
      digitalWrite(LED1, HIGH);

    //digitalWrite(LED2, !digitalRead(NOTCW));
    
    int coilSpeed = 120;
    coilSet(coilSpeed);
    hallISR();
    lastTime = curTime;
  }

  spiRead();

  delay(1);  
}
