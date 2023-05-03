#include <ctype.h>
#include <Keypad.h>
#include "DHT.h"
#include "Wire.h"
#include "LiquidCrystal_AIP31068_I2C.h"
#include <Wire.h>
#include "RTClib.h"

// CONSTANTS
#define BAUD_RATE_9600 100
#define HALF_BAUD_RATE_9600 50
#define BAUD_RATE_4800 188
#define HALF_BAUD_RATE_4800 94
#define RED_LED 5
#define GREEN_LED 4
#define BLUE_LED 3
#define DHT_PIN 2


DHT dhtSensor(DHT_PIN, DHT22);
LiquidCrystal_AIP31068_I2C  lcdDisplay(0x3E, 16, 2);
RTC_DS1307 rtcClock;
const byte numRows = 4;
const byte numCols = 3;
char keyMatrix[numRows][numCols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowConnections[numRows] = {3, 4, 5, 6};
byte colConnections[numCols] = {9, 8, 7};
Keypad customKeypad = Keypad(makeKeymap(keyMatrix), rowConnections, colConnections, numRows, numCols);
char keyPressed;
char weekDays[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
byte rxPin = 0;
byte txPin = 1;
byte switchVal;
extern uint8_t BigNumbers[];

void setup() {
	timeElapsed = 0;
	Serial.begin(9600);

	if (!rtcClock.begin()) {
		Serial.println("Cannot find RTC");
		while (1);
	}
	if (!rtcClock.isrunning()) {
		Serial.println("Set the RTC to compile time");
		rtcClock.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}

	pinMode(11, OUTPUT);
	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(BLUE_LED, OUTPUT);
	Serial.println("Test DHT");
	dhtSensor.begin();
	Serial.println("Test Keypad");
	lcdDisplay.init();
	lcdDisplay.setCursor(1, 0);
	lcdDisplay.print("HELLO");
	lcdDisplay.setCursor(8, 1);
	lcdDisplay.print("WORLD");
}

void displayDateTime() {
	DateTime currentTime = rtcClock.now();
	Serial.println("Current Date & Time: ");
	Serial.print(currentTime.year(), DEC);
	Serial.print('/');
	Serial.print(currentTime.month(), DEC);
	Serial.print('/');
	Serial.print(currentTime.day(), DEC);
	Serial.print(" (");
	Serial.print(weekDays[currentTime.dayOfTheWeek()]);
	Serial.print(") ");
	Serial.print(currentTime.hour(), DEC);
	Serial.print(':');
	Serial.print(currentTime.minute(), DEC);
	Serial.print(':');
	Serial.print(currentTime.second(), DEC);
	Serial.println();
	delay(1000);
}

void loop() {
	//Buzzer
	playShortBeep();
	playStartupBeep();
	tone(11, 200);
	delay(200);
	//LEDs
	digitalWrite(RED_LED, HIGH);
	digitalWrite(GREEN_LED, LOW);
	digitalWrite(BLUE_LED, LOW);
	delay(1000);
	digitalWrite(RED_LED, LOW);
	digitalWrite(GREEN_LED, HIGH);
	digitalWrite(BLUE_LED, LOW);
	delay(1000);
	digitalWrite(RED_LED, LOW);
	digitalWrite(GREEN_LED, LOW);
	digitalWrite(BLUE_LED, HIGH);
	delay(1000);
	while (keyPressed == NO_KEY) {
		keyPressed = customKeypad.getKey();
		delay(100);
	}
	if (keyPressed) {
		Serial.println(keyPressed);
	}
	keyPressed = NULL;
	Serial.println("----");
	float temperature = dhtSensor.readTemperature();
	Serial.println("Temperature :");
	Serial.println(temperature);
	lcdDisplay.noDisplay();
	delay(1000);
	lcdDisplay.display();
	delay(1000);
}

void playShortBeep() {
	tone(11, 200);
	delay(200);
}

void playStartupBeep() {
	tone(11, 300);
	delay(1000);
	tone(11, 300);
	delay(1000);
	tone(11, 300);
	delay(1000);
}
