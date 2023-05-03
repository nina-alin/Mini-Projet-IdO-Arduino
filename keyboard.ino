#include <ctype.h>
#include <FastLED.h>
#include <Keypad.h>
#include "Wire.h"
#include "LiquidCrystal_AIP31068_I2C.h"

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94
#define LED_PIN     10
#define NUM_LEDS    5
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
LiquidCrystal_AIP31068_I2C  LCD(0x3E,16,2); 
const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {3, 4, 5, 6}; 
byte colPins[COLS] = {9,8,7};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char keypress;
byte rx = 19;
byte tx = 18;
byte SWval;
extern uint8_t BigNumbers[];
int pinCount =8;
int time;

void setup()
{
	time=0;
	Serial.begin(9600);
	Serial.println("Test 4x3 keypad");
	LCD.init(); 
   	LCD.setCursor(1, 0);
   	LCD.print("HELLO");
   	LCD.setCursor(8, 1);
  	LCD.print("WORLD");	
}

void loop()
{

	while(keypress == NO_KEY){
		keypress = keypad.getKey();
		delay(100);
	}
	
	if (keypress){
		Serial.println(keypress);
	}
	keypress = NULL;
	Serial.println("----");
	LCD.noDisplay();
	delay(1000);
  	LCD.display();
   	delay(1000);
};
