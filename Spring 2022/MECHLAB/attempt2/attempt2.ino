#include <RTC.h>

#include <Wire.h>

/*
  SD card datalogger

  This example shows how to log data from three analog sensors
  to an SD card using the SD library.

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created  24 Nov 2010
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>

static DS3231 RTC;

  unsigned long hours = 10; //0.05 = 3 min
  unsigned long ms = hours * 3600 * 1000;
  int rate = 2; //10 a second = 100
  unsigned long t;
  String fileName = "today.csv";
  bool finished = false;
  float rainfall = 0;
  float resistance = 0;
  float sameDrop = 0;


const int chipSelect = 4;



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

RTC.begin();

  //RTC.stopClock();

  Serial.print("Is Clock Running: ");
  if (RTC.isRunning())
  {
    Serial.println("Yes");
    Serial.print(RTC.getDay());
    Serial.print("-");
    Serial.print(RTC.getMonth());
    Serial.print("-");
    Serial.print(RTC.getYear());
    Serial.print(" ");
    Serial.print(RTC.getHours());
    Serial.print(":");
    Serial.print(RTC.getMinutes());
    Serial.print(":");
    Serial.print(RTC.getSeconds());
    Serial.print("");
    if (RTC.getHourMode() == CLOCK_H12)
    {
      switch (RTC.getMeridiem()) {
      case HOUR_AM:
        Serial.print(" AM");
        break;
      case HOUR_PM:
        Serial.print(" PM");
        break;
      }
    }
    Serial.println("");
  delay(1000);
  }
  else
  {
    delay(200);

    Serial.println("No");
    Serial.println("Setting Time");
    RTC.setHourMode(CLOCK_H12);
    //RTC.setHourMode(CLOCK_H24);
    RTC.setDateTime(__DATE__, __TIME__);
    Serial.println("New Time Set");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.println(__TIME__);
    RTC.startClock();
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
Serial.println("card initialized.");




}
