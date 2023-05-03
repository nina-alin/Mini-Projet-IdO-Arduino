#include <ctype.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94
#define RED 31
#define GRN 33
#define BLU 35

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
	pinMode(RED, OUTPUT);
   	pinMode(GRN, OUTPUT);
   	pinMode(BLU, OUTPUT);
}

void loop()
{
   digitalWrite(RED, HIGH);
   digitalWrite(GRN, LOW);
   digitalWrite(BLU, LOW);
   delay(1000);
   digitalWrite(RED, LOW);
   digitalWrite(GRN, HIGH);
   digitalWrite(BLU, LOW);
   delay(1000);
   digitalWrite(RED, LOW);
   digitalWrite(GRN, LOW);
   digitalWrite(BLU, HIGH);
   delay(1000);
};
