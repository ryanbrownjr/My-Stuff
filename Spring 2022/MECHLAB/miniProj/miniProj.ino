const int greenLEDPin = 9;
const int redLEDPin = 5;
const int blueLEDPin = 6;
const int sensorPin = A0;
const float baselineTemp = 20.0;
 
  int sensorValue;
  int sensorLow = 1023;
  int sensorHigh = 0;
  const int ledPin = 4;
  int notes[] = {262, 294, 330, 349};
 
    int mutePin = 0;
 
  
 
void setup() {
  Serial.begin(9600);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
 
  pinMode(3, INPUT);
  
  for(int pinNumber = 2; pinNumber<5; pinNumber++)
    {pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
 
    pinMode(greenLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);
    pinMode(blueLEDPin, OUTPUT);
  }
}
 
void loop() {
mutePin = digitalRead(3);
if(mutePin == HIGH){
  
  int sensorVal = analogRead(sensorPin);
  delay(100);
 
  float voltage = (sensorVal/1024.0)*5;
 
  float temperature = (voltage - .5)*100;
  Serial.print(sensorVal);
  Serial.print(",");
  Serial.print(voltage);  
  Serial.print(",");
  Serial.print(temperature);  
  Serial.print(",");

 if(sensorVal = 190){
    analogWrite(blueLEDPin, 100);
    analogWrite(redLEDPin, 100);
    analogWrite(greenLEDPin, 100);
  }
 
  else if(sensorVal >= 200 && sensorVal <= 180){
    analogWrite(blueLEDPin, 0);
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 100);
  }
 
  else if(sensorVal > 200){
    analogWrite(blueLEDPin, 0);
    analogWrite(redLEDPin, 100);
    analogWrite(greenLEDPin, 0);
  }
  
  else if(sensorVal < 180){
    analogWrite(blueLEDPin, 100);
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
  }
  
  else{
}
  int lightLevel = analogRead(A1);
   Serial.print(lightLevel);
   Serial.print(",");
   Serial.println();
  if(lightLevel > 768 && lightLevel <= 1022){
    tone(4, notes[0]);
  }
 
  else if(lightLevel > 512 && lightLevel <= 768){
    tone(4, notes[1]);
  }
 
  else if(lightLevel > 256 && lightLevel <= 512){
    tone(4, notes[2]);
  }
  
  else if(lightLevel >= 0 && lightLevel <= 256){
    tone(4, notes[3]);
  }
  
  else{
    noTone(4);
  }
 
}
else if(mutePin == LOW){
  noTone(4);
  analogWrite(blueLEDPin, 0);
  analogWrite(redLEDPin, 0);
  analogWrite(greenLEDPin, 0);
  }


}
