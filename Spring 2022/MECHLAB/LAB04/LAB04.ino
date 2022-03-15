#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5 ,d6, d7);
const int startPin = 6; // stop/start button
const int lapPin = 7; 
int startVal;
boolean timing = false;
int elapsedTime = 0;
int previousTime = 0;
long startTime;
char timeLine[16];
int minutes = 0;
int seconds = 0;
char lapLine[16];
int lapVal;
int oldTime = 0;
long lapTime;
int lapMin;
int lapSec;
void setup() {
pinMode (startPin, INPUT);
pinMode (lapPin, INPUT);
  lcd.begin(16, 2);
  lcd.print("Stopwatch");
  lcd.setCursor(0,1);
  lcd.print("Press Start");
}
void loop() {
startVal = digitalRead(startPin);
if(startVal == HIGH) {
  delay(500);
  lcd.clear();
  startTime=millis()/1000;
  timing = true;
}
while(timing == true) {
  elapsedTime = previousTime + (millis()/1000 - startTime);
  seconds = elapsedTime % 60;
  minutes = (elapsedTime - seconds)/60;
 delay(15);
  lcd.setCursor(0, 0);
  if(seconds < 10){
      sprintf(timeLine, "Time:    %d:0%d", minutes, seconds);
  }
  else{
  sprintf(timeLine, "Time:     %d:%d", minutes, seconds);
  }
  lcd.print(timeLine);
lapVal = digitalRead(lapPin);
if(lapVal == HIGH) {
  delay(500);
  lcd.clear();
  lapTime=elapsedTime-oldTime;
  oldTime = elapsedTime;
  lapSec = lapTime % 60;
  lapMin = (lapTime - lapSec)/60;
  delay(15);
  lcd.setCursor(0,1);
  if(lapSec < 10) {
  sprintf(lapLine, "Lap:   %d:0%d", lapMin, lapSec);
  }
  else{
    sprintf(lapLine, "Lap:   %d:%d", lapMin, lapSec);
  }

  lcd.print(lapLine);
  }
startVal = digitalRead(startPin);
if(startVal == HIGH) {
  timing = false;
  previousTime=elapsedTime;
  delay(500);
  }
}
}
