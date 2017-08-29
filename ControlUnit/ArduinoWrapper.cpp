#include "ArduinoWrapper.h"
#include <Arduino.h>
#include "Constants.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); //0x3f

ArduinoWrapper::ArduinoWrapper()
{
	lcd.begin();
	lcd.backlight();
}

int ArduinoWrapper::DigitalRead(unsigned int port)
{
	return digitalRead(port);
}

void ArduinoWrapper::DigitalWrite(unsigned int port, int value)
{
	digitalWrite(port, value);
}

int ArduinoWrapper::AnalogRead(unsigned int port)
{
	return analogRead(port);
}

void ArduinoWrapper::AnalogWrite(unsigned int port, int value)
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

void ArduinoWrapper::Print(double val, int dp = 2)
{
	lcd.print(val, dp);
}

void ArduinoWrapper::SerialPrint(char * message)
{
	Serial.println(message);
}

void ArduinoWrapper::PrintFormat(char * message, ...)
{
	char buffer[SCREEN_BUFFER_SIZE];
	va_list args = nullptr;
	va_start(args, message);
	vsnprintf(buffer, SCREEN_BUFFER_SIZE, message, args);
	va_end(args);

	lcd.print(message);
}

void ArduinoWrapper::EngageLoader(bool forward, bool enable)
{
	if(!enable)
	{
		DigitalWrite(LOADER_ENABLE_PORT, ARDUINO_HIGH);
		DigitalWrite(LOADER_FWD_PORT, ARDUINO_LOW);
		DigitalWrite(LOADER_REV_PORT, ARDUINO_LOW);
	}
	else
	{
		DigitalWrite(LOADER_ENABLE_PORT, ARDUINO_LOW);
		DigitalWrite(LOADER_FWD_PORT, forward ? ARDUINO_LOW : ARDUINO_HIGH);
		DigitalWrite(LOADER_REV_PORT, forward ? ARDUINO_LOW : ARDUINO_HIGH);
	}
}

void ArduinoWrapper::EngageFan(bool enable)
{
	DigitalWrite(FAN_PORT, enable ? ARDUINO_LOW : ARDUINO_HIGH);
}

double ArduinoWrapper::GetBatteryVoltage()
{
	auto vlt = AnalogRead(VOLTAGE_PORT);
	auto calculated = static_cast<double>(vlt) * ANALOG_COEFFICIENT * VOLTAGE_COEFFICIENT;

	return calculated;
}

void ArduinoWrapper::EngageInjector(bool enable)
{
	DigitalWrite(INJECTOR_PORT, enable ? ARDUINO_HIGH : ARDUINO_LOW);
}

void ArduinoWrapper::EngageBreach(bool open, bool enable)
{
	if(!enable)
	{
		DigitalWrite(BREACH_OPEN_PORT, ARDUINO_LOW);
		DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_LOW);
	}
	else
	{
		DigitalWrite(BREACH_OPEN_PORT, open ? ARDUINO_LOW : ARDUINO_HIGH);
		DigitalWrite(BREACH_CLOSE_PORT, open ? ARDUINO_HIGH : ARDUINO_LOW);
	}	
}
