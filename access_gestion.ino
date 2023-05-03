#include <ctype.h>
#include "Wire.h"
#include "LiquidCrystal_AIP31068_I2C.h"
#include <Keypad.h>
#include <Wire.h>
#include "RTClib.h"

// CONSTANTS
#define PASSWORD "1234"
#define NIGHT_PASSWORD "0000"
#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94
#define PIN_LED 45
#define RED1 30 
#define GRN1 31 
#define BLU1 32
#define RED2 33 
#define GRN2 34 
#define BLU2 35
#define RED3 36 
#define GRN3 37 
#define BLU3 38 
#define RED4 39 
#define GRN4 40 
#define BLU4 41
#define RED5 42 
#define GRN5 43 
#define BLU5 44

LiquidCrystal_AIP31068_I2C  LCD(0x3E,16,2); 
int nled;
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
int nbError;
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
byte rx = 19;
byte tx = 18;
byte SWval;
extern uint8_t BigNumbers[];
int pinCount =8;
int time;
int idle;
String mdp = "";
int validation;
int nightValidation;
boolean firstMdpOK;

void setup()
{
	time=0;
	Serial.begin(9600);
	idle = 0; 
	mdp = "";
	validation = 1; 
	int nbError = 0;
	pinMode(RED1, OUTPUT);pinMode(GRN1, OUTPUT);pinMode(BLU1, OUTPUT);
	pinMode(RED2, OUTPUT);pinMode(GRN2, OUTPUT);pinMode(BLU2, OUTPUT);
	pinMode(RED3, OUTPUT);pinMode(GRN3, OUTPUT);pinMode(BLU3, OUTPUT);
	pinMode(RED4, OUTPUT);pinMode(GRN4, OUTPUT);pinMode(BLU4, OUTPUT);
	pinMode(RED5, OUTPUT);pinMode(GRN5, OUTPUT);pinMode(BLU5, OUTPUT);
	int nled = 0;
	pinMode(11, OUTPUT);
	startBuzzer();
	if (!rtc.begin()) {
    		Serial.println("Cannot find RTC");
    		while (1);
  	}
	if (!rtc.isrunning()) {
    		Serial.println("Set the time");
      		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 	}

}	

void orangeLeds(){
	ledsOff();
	if(nled%5 == 0){
		digitalWrite(RED1, HIGH);digitalWrite(GRN1, HIGH);digitalWrite(BLU1, LOW);
	}
	if(nled%5 == 1){
		digitalWrite(RED2, HIGH);digitalWrite(GRN2, HIGH);digitalWrite(BLU2, LOW);
	}
	if(nled%5 == 2){
		digitalWrite(RED3, HIGH);digitalWrite(GRN3, HIGH);digitalWrite(BLU3, LOW);
	}
	if(nled%5 == 3){
		digitalWrite(RED4, HIGH);digitalWrite(GRN4, HIGH);digitalWrite(BLU4, LOW);
	}
	if(nled%5 == 4){
		digitalWrite(RED5, HIGH);digitalWrite(GRN5, HIGH);digitalWrite(BLU5, LOW);
	}
	nled = nled + 1;
}
void greenLeds(){
	ledsOff();
	digitalWrite(RED1, LOW);digitalWrite(GRN1, HIGH);digitalWrite(BLU1, LOW);
	digitalWrite(RED2, LOW);digitalWrite(GRN2, HIGH);digitalWrite(BLU2, LOW);
	digitalWrite(RED3, LOW);digitalWrite(GRN3, HIGH);digitalWrite(BLU3, LOW);
	digitalWrite(RED4, LOW);digitalWrite(GRN4, HIGH);digitalWrite(BLU4, LOW);
	digitalWrite(RED5, LOW);digitalWrite(GRN5, HIGH);digitalWrite(BLU5, LOW);
}
void redLeds(){
	ledsOff();
	digitalWrite(RED1, HIGH);digitalWrite(GRN1, LOW);digitalWrite(BLU1, LOW);
	digitalWrite(RED2, HIGH);digitalWrite(GRN2, LOW);digitalWrite(BLU2, LOW);
	digitalWrite(RED3, HIGH);digitalWrite(GRN3, LOW);digitalWrite(BLU3, LOW);
	digitalWrite(RED4, HIGH);digitalWrite(GRN4, LOW);digitalWrite(BLU4, LOW);
	digitalWrite(RED5, HIGH);digitalWrite(GRN5, LOW);digitalWrite(BLU5, LOW);
}

void ledsOff(){
	digitalWrite(RED1, LOW);digitalWrite(GRN1, LOW);digitalWrite(BLU1, LOW);
	digitalWrite(RED2, LOW);digitalWrite(GRN2, LOW);digitalWrite(BLU2, LOW);
	digitalWrite(RED3, LOW);digitalWrite(GRN3, LOW);digitalWrite(BLU3, LOW);
	digitalWrite(RED4, LOW);digitalWrite(GRN4, LOW);digitalWrite(BLU4, LOW);
	digitalWrite(RED5, LOW);digitalWrite(GRN5, LOW);digitalWrite(BLU5, LOW);
}

void lcdOff(){
	 LCD.noDisplay();
}
void passwordLcd(){
	LCD.init();
	LCD.setCursor(2, 5);
  	LCD.print("ENTER CODE");
   	LCD.display();
}

void passwordNightLcd(){
	LCD.init();
	LCD.setCursor(2, 5);
  	LCD.print("ENTER NIGHT CODE");
   	LCD.display();
}

void acceptMDP(){
	LCD.init();
	LCD.setCursor(2, 5);
  	LCD.print("GOOD CODE");
   	LCD.display();
}

void wrongPasswordLcd(){
	LCD.init();
	LCD.setCursor(2, 5);
  	LCD.print("WRONG CODE");
   	LCD.display();
}

void accessDeniedLcd(){
	LCD.init();
	LCD.setCursor(2, 5);
  	LCD.print("ACCES BLOQUE");
   	LCD.display();
}
void stopLcd(){
	LCD.init();
	LCD.setCursor(2, 5);
  	LCD.print("GOODBYE !");
   	LCD.display();
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

void etapeIDLE(){
	greenLeds();
	while(keypress == NO_KEY){
		delay(100);
		time += 100;
		keypress = keypad.getKey();
		
	}
	
	if(isNight()==true){
		digitalWrite(PIN_LED, HIGH);
	}else{
		digitalWrite(PIN_LED, LOW);
	}
	
	if (keypress){
		idle = 1;
		keypress = NO_KEY;
		mdp = "";
		validation = 1;
		nightValidation = 1;
		bipBuzzer();
		firstMdpOK = false;
	}

}

boolean isNight(){
	DateTime now = rtc.now();
    	if(now.hour() < 6 && 20 > now.hour())
            return false;
	Serial.print("hour : ");
	Serial.println(now.hour());
	return true;
}

void loop() {
	if(nbError > 2){
		Serial.println("BLOCK");
		redLeds();
		accessDeniedLcd();
	}
	if (idle == 0){
		Serial.println("IDLE");
		etapeIDLE();
	}
	if(idle == 1 && validation == 1 && nbError < 3){ 
		Serial.println("VALIDATION");
		passwordLcd();
		while(keypress == NO_KEY){
			keypress = keypad.getKey();
			if(time%500 == 0) orangeLeds();
			delay(100);
			time+=100;
		}
		if(keypress == '*'){
			validation = 0;
			Serial.println("Password ok");
			
		}else if(keypress == '#'){
			idle = 0;
			stopLcd();
			Serial.println("Going back to IDLE");
		}else {
			mdp += keypress;
			bipBuzzer();
			Serial.println(mdp);
		}
		if (keypress){
			keypress = NO_KEY;
		}
		
	}
	

	if(validation == 0 && firstMdpOK == false){	
		Serial.println("VALIDATION");
		if(mdp.equals(PASSWORD)){
			Serial.println("OK");
			buzzerOk();
			acceptMDP();
			if(isNight() == false){
				idle = 0;
			}else{
				Serial.println("Night password asked");
				firstMdpOK = true;
			}
			mdp= "";
		}else{ 
			Serial.println("KO");
			buzzerError();
			wrongPasswordLcd();
			ledsOff();
			delay(750);
			redLeds();
			delay(750);
			ledsOff();
			delay(750);
			redLeds();
			delay(750);
			ledsOff();
			delay(750);
			redLeds();
			delay(750);
			nbError =  nbError + 1;
			idle = 0;
		}
	}
	
	if(isNight() == true && idle == 1 && validation == 0 && nightValidation == 1 && nbError < 3){ 
		Serial.println("Password night");
		passwordNightLcd();

		while(keypress == NO_KEY){
			keypress = keypad.getKey();
			if(time%500 == 0) ledsOrange();
			delay(100);
			time+=100;
		}
		if(keypress == '*'){
			nightValidation = 0;
			Serial.println("Password night");
			
		}else if(keypress == '#'){
			idle = 0;
			stopLcd();
			Serial.println("Going back to IDLE");
		}else {
			mdp += keypress;
			bipBuzzer();
			Serial.println(mdp);
		}
		if (keypress){
			keypress = NO_KEY;
		}
		
	}
	
    	if(nightValidation == 0){	
		Serial.println("VALIDATION NIGHT");
		if(mdp.equals(NIGHT_PASSWORD)){
			Serial.println("Password night OK");
			buzzerOk();
			acceptMDP();
			idle = 0;
			nbError = 0;
			mdp= "";
		}else{ 
			Serial.println("Password night KO");
			buzzerError();
			ledsOff();
			delay(750);
			wrongPasswordLcd();
			redLeds();
			delay(750);
			redLeds();
			delay(750);
			redLeds();
			delay(750);
			nbError =  nbError + 1;
			idle = 0;
		}
	}
};