#include "ArduinoWrapper.h"
#include <Arduino.h>
#include "Constants.h"
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); //0x3f
#define DHTTYPE DHT11  

DHT dht(TEMP_HUM_SENSOR_PORT, DHTTYPE);

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

float ArduinoWrapper::GetAtmPressure()
{
	return 0.0f;
}

float ArduinoWrapper::GetInternalTemp()
{
	return 0.0f;
}

float ArduinoWrapper::GetExternalTemp()
{
	auto t = dht.readTemperature();
	return t;
}

float ArduinoWrapper::GetExternalHumidity()
{
	auto h = dht.readHumidity();
	if(isnan(h))
	{
		return 0.0f;
	}
	return h;
}

float ArduinoWrapper::GetReceiverPressure()
{
	auto press = AnalogRead(RECEIVER_PRESSURE_PORT);
	auto val = double(press) * ANALOG_COEFFICIENT;

	if(val < 0.5f)
	{
		return -1;
	}

	return val * PRESSURE_COEFFICIENT;
}

void ArduinoWrapper::ResetDebouncingTriggers()
{
	DigitalWrite(BLAST_TRIGGER_RESET_PORT, ARDUINO_LOW);
	DigitalWrite(SS_TRIGGER_RESET_PORT, ARDUINO_HIGH);
	Delay(50);
	DigitalWrite(BLAST_TRIGGER_RESET_PORT, ARDUINO_HIGH);
	DigitalWrite(SS_TRIGGER_RESET_PORT, ARDUINO_LOW);
}

bool ArduinoWrapper::GetAmmoSensorState()
{
	auto result = DigitalRead(AMMO_SENSOR_PORT);
	return result == ARDUINO_LOW;
}

void ArduinoWrapper::EngageIngnition(bool enabled)
{
	DigitalWrite(IGNITION_PORT, enabled ? ARDUINO_LOW : ARDUINO_HIGH);
}

void ArduinoWrapper::EngageInjectorDiode(bool enabled)
{
	DigitalWrite(IGNITION_PORT, enabled ? ARDUINO_HIGH : ARDUINO_LOW);
}
