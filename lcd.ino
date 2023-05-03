#include "Wire.h"
#include "LiquidCrystal_AIP31068_I2C.h"
#include <ctype.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94

LiquidCrystal_AIP31068_I2C  LCD(0x3E,16,2); 
byte rx = 0;
byte tx = 1;
byte SWval;
extern uint8_t BigNumbers[];
int pinCount =8;
int time;

void setup()
{
	time=0;
	Serial.begin(9600);
	LCD.init();
	LCD.setCursor(1, 0);
   	LCD.print("HELLO");
   	LCD.setCursor(8, 1);
   	LCD.print("WORLD");
}


void loop()
{
	LCD.noDisplay();
   	delay(1000);
   	LCD.display();
   	delay(1000);
};
