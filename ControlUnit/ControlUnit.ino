//#include "HwCheckSequence.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); //0x3f

void setup() 
{
	lcd.begin();
	lcd.backlight();
}

void loop() 
{
	lcd.setCursor(1, 1);
	lcd.print("Kurkas");

	delay(1000);

	
	
}

