#include <ctype.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94

byte rx = 0;
byte tx = 1;
byte SWval;
extern uint8_t BigNumbers[];
int pinCount =8;
int temps;

void setup()
{	
	pinMode(11, OUTPUT);
}	


void bipBuzzer(){
	tone(11, 200);
	delay(200);
	buzzerOff();
}

void startBuzzer(){
	tone(11, 300);
	delay(1000);
	
	buzzerOff();
	delay(1000);
	
	tone(11, 300);
	delay(1000);
	
	buzzerOff();
	delay(1000);
	
	tone(11, 300);
	delay(1000);
	
	buzzerOff();
	delay(1000);
}

void buzzerOk(){
	tone (11, 200);
	delay(1000);
	buzzerOff();
}

void buzzerError(){
	tone (11, 400);
	delay(1000);
	buzzerOff();
}

void buzzerOff(){
	noTone(11);
}

void loop()
{
	bipBuzzer();
	startBuzzer();
	tone(11, 200); 
     delay(200);
};
