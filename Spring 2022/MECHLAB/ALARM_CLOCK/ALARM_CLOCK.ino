//LEDs are 8-13; Button is 5; buzzer is 7
int tenSecPin = 13, twentySecPin = 12, thirtySecPin = 11, fortySecPin = 10, fiftySecPin = 9, oneMinutePin = 8, reset = 5, buzzer = 7;
int notes[] = {262};
int sec, startTime = 0;
boolean started=false, alarmOver=false, threeSecondTime=false;

void setup() {
  Serial.begin(9600);
  pinMode(tenSecPin, OUTPUT);//changed these so they aren't hardcoded
  pinMode(twentySecPin, OUTPUT);
  pinMode(thirtySecPin, OUTPUT);
  pinMode(fortySecPin, OUTPUT);
  pinMode(fiftySecPin, OUTPUT);
  pinMode(oneMinutePin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(reset, INPUT);
}

void loop() {
  int sec = (millis() / 1000) - startTime;
  if (digitalRead(reset) == HIGH) {
    alarmOver=false, threeSecondTime=false;
    startTime=millis()/1000;
    started=true;
    digitalWrite(tenSecPin, LOW);
    digitalWrite(twentySecPin, LOW);
    digitalWrite(thirtySecPin, LOW);
    digitalWrite(fortySecPin, LOW);
    digitalWrite(fiftySecPin, LOW);
    digitalWrite(oneMinutePin, LOW);  
  }
  if(started){
    switch (sec) {
      case 60:
        digitalWrite(oneMinutePin, HIGH);
      case 50:
        digitalWrite(fiftySecPin, HIGH);
      case 40:
        digitalWrite(fortySecPin, HIGH);
      case 30:
        digitalWrite(thirtySecPin, HIGH);
      case 20:
        digitalWrite(twentySecPin, HIGH);
      case 10:
        digitalWrite(tenSecPin, HIGH);
      break;
      default:
      if (sec>=60) {
        alarmOver=true;
        started=false;
        threeSecondTime=true;  
      }   
      break;
    }//end of switch/case method
    
  }else if(alarmOver&&threeSecondTime){
    tone(7, notes[0]);
    delay(100);
    noTone(7);
    threeSecondTime=false;
    startTime=millis()/1000;
  }else if(alarmOver&&sec>=3){
    threeSecondTime=true;
  }
  delay(15);
}
