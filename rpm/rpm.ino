#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

const int rpmSensor = 3;//IR sensor INPUT


unsigned long lastRev = 0;
unsigned int revs = 0;
unsigned long timeold = 0;
unsigned long lastUpdate = 0;
volatile bool singleRev = false;

unsigned int rpm;
unsigned int lastrpm;

void addRev(){
  
  if(millis() - lastRev > 1){
    singleRev = true;
    lastRev = millis();
  }
  //singleRev = true;
}

void setup()
{
  lcd.begin(16,2);
  pinMode(rpmSensor, INPUT_PULLUP);       
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(rpmSensor), addRev, RISING);
}

void loop()
{
  if(singleRev && digitalRead(rpmSensor) == LOW){
    //Serial.println(revs);
    revs ++;
    singleRev = false;
  }

  if (revs >= 5) { 
     rpm = 30*1000/(millis() - timeold)*revs*2;
     timeold = millis();
     revs = 0;
   }

  if(millis()-lastRev > 1000){
    rpm = 0;
  }

  if(millis() - lastUpdate > 200){
    Serial.println(rpm,DEC);
    if(abs(lastrpm - rpm) < 200){
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(rpm);
      lcd.print(" rpm");
    }else if(rpm > lastrpm){
      rpm += 20;
    }else{
      rpm -+ 20;
    }
    lastUpdate = millis();
    lastrpm = rpm;
  }
}
