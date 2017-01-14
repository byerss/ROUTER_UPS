/*
2017 Stephen Byers
 */

float killThreshold = 10.8;

void setup() {

  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2),powerLoss,RISING); //PIN2 Pulled high when no AC power
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(4, LOW);
}

void loop() {

  int sensorVal = digitalRead(2);
  


  if (sensorVal == HIGH) {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    Serial.print("ON BATTERY ... ");
    int rawVolt = analogRead(5);
    float voltage = (rawVolt * 0.004883 + 10);
    Serial.print("Voltage = ");
    Serial.print(voltage);
    Serial.println("V");

    if (voltage <= killThreshold) {
      Serial.println("VOLTAGE CRITICAL - SENDING KILL SWITCH!");
      digitalWrite(3, HIGH);
      delay(100);
    }
    
  } else {
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    Serial.println("ON LINE POWER");
   }
delay(2000);

}




void powerLoss() {

  
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  Serial.println("POWERLOSS DETECTED!");
}


