#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
byte rx = 19;
byte tx = 18;
byte SWval;

void setup () 
{
  Serial.begin(9600);
  delay(3000); 
  if (!rtc.begin()) {
    Serial.println("Cannot find RTC");
    while (1);
  }
  if (!rtc.isrunning()) {
    Serial.println("Set the RTC to compile time");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop () 
{
    DateTime now = rtc.now();
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    Serial.println();
    delay(1000);
}