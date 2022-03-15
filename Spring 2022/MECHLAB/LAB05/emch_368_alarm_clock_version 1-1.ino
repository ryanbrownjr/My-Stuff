unsigned long previousTime = 0UL, buzzerTimetoPlay = 300UL, timeBetweenBuzzer = 3000UL;
const int amountOfTime = 60, firstLED = 8, numberOfLEDs = 6, buzzer = 7, button = 6;
int buttonState;
boolean ringAlarm = true, runPart = false, buttonPressed = false;

void setup() {
  for (int x = firstLED; x < firstLED + numberOfLEDs; x++) {
    pinMode(x, OUTPUT); //initialises the LEDs
  }//end of for loop
  pinMode(button, INPUT);//initialises button pin
  pinMode(buzzer, OUTPUT);//initialises buzzer pin
}//end of setup method

void loop() {
  buttonState = digitalRead(button);//gets button's state
  if (buttonState == HIGH) {//if button has been pressed, do X
    digitalWrite(buzzer, LOW);//turns buzzer off
    buttonPressed = true;//lets system know button was pressed once and cycle was started
    switchPinStates(numberOfLEDs , firstLED, LOW, 0);//turns all LEDs off without any delay
    switchPinStates(numberOfLEDs , firstLED, HIGH, amountOfTime/numberOfLEDs * 1000);//for milliseconds vs seconds
    //for testing purposes, change the 1000 above to a smaller number, such as 100
    ringAlarm = true;//set ringAlarm boolean true (rings alarm, duh)
  }else if (ringAlarm && buttonPressed) {//if timer has finished becuase ringAlarm is true and button has been pressed, indicating at least 1 cycle has run
    digitalWrite(buzzer, HIGH);
    previousTime = millis();
    ringAlarm = false;
  }//end of 1st level if
  if (!ringAlarm && buttonPressed) {//if alarm has run once and is ready to be truned off  and button has been pressed, indicating at least 1 cycle has run
    if (millis() - previousTime > timeBetweenBuzzer && runPart) {//if current Time-the Time when alarm was turned off is larger than 3 seconds-> 
      //AND runPart boolean for letting us know when to turn alarm back on is true
	  ringAlarm = true;//turn alarm on
      runPart = false;//dont run this part agian until other section is done
    } else if (millis() - previousTime > buzzerTimetoPlay && !runPart) {//if current Time-the Time when alarm was turned on is larger than 0.3 seconds-> 
      //AND runPart boolean for letting us know when to turn alarm back on is true
      digitalWrite(buzzer, LOW);//turn buzzer off
      previousTime = millis();//set previoustime to time when alarm turns off
      runPart = true;// tell arduino to get ready to turn buzzer on after 3 seconds
    }//ending bracket of 2nd level if
  }//ending bracket of 1st level if
}//ending bracket of loop method

/*special method/function developed to control a number of pins after a certain amount of delay, specified in milliseconds
* Needs number of pins wanted to have state switched, 
* Needs first pin in list of pins
* Needs what state to put the pins in,
* Needs amount of Delay between setting state of each pin
* Ex. set pins 1,2,3,4 to ON with 5 second delay
* switchPinStates(4, 1, HIGH, 5000);*/
void switchPinStates(int numberOfPins, int firstPin, int state, int amountOfDelay) {
  int x = firstPin;//set temporary variable "x" to the first Pin,
  while (x < numberOfPins + firstPin) {//while x is less than highest pin, by using first Pin + number of Pins
    delay(amountOfDelay);//delays before truning each pin on
    digitalWrite(x, state);//writes the state to each pin after the delay
    x++;//increments x after running through each while loop
  }//ending bracket of while
}//ending bracket of switchLEDStates