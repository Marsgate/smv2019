const int motorOut = 3;
const int throttleIn = A7;

void setup() {  
  pinMode(motorOut, OUTPUT);
  pinMode(throttleIn, INPUT);

  Serial.begin(9600);
}

void loop() {
  //get throttle
  int scaledThrottle = (1000 - analogRead(throttleIn))* 0.28686868686;
  
  if(scaledThrottle < 0)
    scaledThrottle = 0;
  else if(scaledThrottle > 255)
    scaledThrottle = 255;

  Serial.print("Scaled: ");
  Serial.println(scaledThrottle);
  

  //set motor pwm
  analogWrite(motorOut, scaledThrottle);
}
