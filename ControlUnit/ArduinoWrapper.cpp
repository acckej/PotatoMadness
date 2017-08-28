#include "ArduinoWrapper.h"
#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); //0x3f

ArduinoWrapper::ArduinoWrapper()
{
	lcd.begin();
	lcd.backlight();
}

int ArduinoWrapper::DigitalRead(int port)
{
	return digitalRead(port);
}

void ArduinoWrapper::DigitalWrite(int port, int value)
{
	digitalWrite(port, value);
}

int ArduinoWrapper::AnalogRead(int port)
{
	return analogRead(port);
}

void ArduinoWrapper::AnalogWrite(int port, int value)
{
	analogWrite(port, value);
}

void ArduinoWrapper::Delay(unsigned long ms)
{
	delay(ms);
}

void ArduinoWrapper::ClearScreen()
{
	lcd.clear();
}

void ArduinoWrapper::SetScreenCursor(char col, char row)
{
	lcd.setCursor(col, row);
}

void ArduinoWrapper::Print(const char msg[])
{
	lcd.print(msg);
}

void ArduinoWrapper::Print(float val, int dp = 2)
{
	lcd.print(val, dp);
}

void ArduinoWrapper::SerialPrint(char * message)
{
	Serial.println(message);
}
