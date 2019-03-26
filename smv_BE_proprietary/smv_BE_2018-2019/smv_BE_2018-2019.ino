#include <Coil.h>
#include <HallSensor.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <SPI.h>

/*********************************/
//Pin definitions
#define HALL1 22
#define HALL2 21
#define HALL3 20

#define EN_GATE 2
#define NFAULT 0

#define LED1 1

#define DRV_MOSI 11
#define DRV_MISO 12
#define DRV_CLK 13
#define DRV_CS 14

int lastTime = 0;

/*********************************/
//library configuration and object creation

//lcd setup
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//hall sensor setup (pin1, pin2, pin3)
HallSensorController hall(HALL1, HALL2, HALL3);

// Coil setup (positive, negative, offset)
Coil a(10, 9, 0);
Coil b(6, 5, 2);
Coil c(4, 3, 4);

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
  
  Serial.begin(115200);

  //pin mode setting
  pinMode(EN_GATE, OUTPUT);
  pinMode(NFAULT, INPUT);
  pinMode(LED1, OUTPUT);
  
  pinMode(DRV_MOSI, OUTPUT);
  pinMode(DRV_MISO, INPUT);
  pinMode(DRV_CLK, OUTPUT);
  pinMode(DRV_CS, OUTPUT);

  digitalWrite(DRV_CS, HIGH);
  

  //lcd init
  //lcd.begin(16, 2);

  //enable gate 
  digitalWriteFast(EN_GATE, LOW);
  delay(10);
  digitalWriteFast(EN_GATE, HIGH);
  delay(10);
  
  //start spi
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setDataMode(SPI_MODE1);
  
  

  a.set(0);
  b.set(0);
  c.set(0);

  //a.set(10);

  /*
  attachInterrupt(HALL1, hallISR, CHANGE);
  attachInterrupt(HALL2, hallISR, CHANGE);
  attachInterrupt(HALL3, hallISR, CHANGE);
  */
}

/*
void spiRead(byte addr){

  uint16_t dataToSend = 0x0;
  dataToSend |= (0x0010 | addr);
  dataToSend <<= 11;
  //Serial.println(dataToSend, BIN);
  
  SPI.beginTransaction(spi_settings);
  digitalWrite(DRV_CS, LOW);
  

  Serial.println(SPI.transfer16(dataToSend), BIN);

  digitalWrite(DRV_CS, HIGH);
  SPI.endTransaction();
}*/

uint16_t SPIread(uint8_t addr)
{
  digitalWrite(DRV_CS, LOW);

  delayMicroseconds(50);
  uint8_t d = 1 << 7;
  d |= addr << 3;
  SPI.transfer(d);
  SPI.transfer(0);

  digitalWrite(DRV_CS, HIGH);
  delayMicroseconds(30);
  digitalWrite(DRV_CS, LOW);
  
  d = SPI.transfer(1<<7);
  uint16_t resp = d << 8;
  resp |= SPI.transfer(0);

  digitalWrite(DRV_CS, HIGH);

  return resp & 0x7FF;
}

void loop(){

  int curTime = millis();
  if(curTime - lastTime > 50){

    Serial.println(SPIread(0x0), BIN);
    
    if(!digitalRead(NFAULT))
      digitalWrite(LED1, HIGH);
    
    int coilSpeed = 20;
    coilSet(coilSpeed);
    //hallISR();
    lastTime = curTime;
  }

  delay(1);  
}
