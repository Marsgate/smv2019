void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(22, OUTPUT);
  digitalWrite(22, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  Serial.println("On");
  delay(1000);
  digitalWrite(13, LOW);
  Serial.println("Off");
  delay(1000);

  
  delay(1);
}
