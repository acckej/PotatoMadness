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
		digitalWrite(LOADER_ENABLE_PORT, ARDUINO_HIGH);
		digitalWrite(LOADER_FWD_PORT, ARDUINO_LOW);
		digitalWrite(LOADER_REV_PORT, ARDUINO_LOW);
	}
	else
	{
		digitalWrite(LOADER_ENABLE_PORT, ARDUINO_LOW);
		digitalWrite(LOADER_FWD_PORT, forward ? ARDUINO_LOW : ARDUINO_HIGH);
		digitalWrite(LOADER_REV_PORT, forward ? ARDUINO_LOW : ARDUINO_HIGH);
	}
}

void ArduinoWrapper::EngageFan(bool enable)
{
	digitalWrite(FAN_PORT, enable ? ARDUINO_LOW : ARDUINO_HIGH);
}

double ArduinoWrapper::GetBatteryVoltage()
{
	auto vlt = AnalogRead(VOLTAGE_PORT);
	auto calculated = static_cast<double>(vlt) * ANALOG_COEFFICIENT * VOLTAGE_COEFFICIENT;

	return calculated;
}

void ArduinoWrapper::EngageInjector(bool enable)
{
	digitalWrite(INJECTOR_PORT, enable ? ARDUINO_HIGH : ARDUINO_LOW);
}

void ArduinoWrapper::EngageBreach(bool open, bool enable)
{
	if(!enable)
	{
		digitalWrite(BREACH_OPEN_PORT, ARDUINO_LOW);
		digitalWrite(BREACH_CLOSE_PORT, ARDUINO_LOW);
	}
	else
	{
		digitalWrite(BREACH_OPEN_PORT, open ? ARDUINO_LOW : ARDUINO_HIGH);
		digitalWrite(BREACH_CLOSE_PORT, open ? ARDUINO_HIGH : ARDUINO_LOW);
	}	
}

float ArduinoWrapper::GetAtmPressure()
{
	return 1.0f;
}

float ArduinoWrapper::GetInternalTemp()
{
	return 1.0f;
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
	auto press = analogRead(RECEIVER_PRESSURE_PORT);
	auto val = double(press) * ANALOG_COEFFICIENT;

	if(val < 0.45f)
	{
		return -1;
	}

	return (val - PRESSURE_CONSTANT) * PRESSURE_COEFFICIENT;
}

void ArduinoWrapper::ResetDebouncingTriggers()
{
	digitalWrite(BLAST_TRIGGER_RESET_PORT, ARDUINO_LOW);
	digitalWrite(SS_TRIGGER_RESET_PORT, ARDUINO_HIGH);
	Delay(50);
	digitalWrite(BLAST_TRIGGER_RESET_PORT, ARDUINO_HIGH);
	digitalWrite(SS_TRIGGER_RESET_PORT, ARDUINO_LOW);
}

bool ArduinoWrapper::GetAmmoSensorState()
{
	auto result = digitalRead(AMMO_SENSOR_PORT);
	return result == ARDUINO_LOW;
}

void ArduinoWrapper::EngageIngnition(bool enabled)
{
	digitalWrite(IGNITION_PORT, enabled ? ARDUINO_LOW : ARDUINO_HIGH);
}

void ArduinoWrapper::EngageInjectorDiode(bool enabled)
{
	digitalWrite(INJ_LED_PORT, enabled ? ARDUINO_HIGH : ARDUINO_LOW);
}

void ArduinoWrapper::Init()
{
	lcd.begin();
	lcd.backlight();

	pinMode(LOADER_FWD_PORT, OUTPUT);
	pinMode(LOADER_REV_PORT, OUTPUT);
	pinMode(LOADER_ENABLE_PORT, OUTPUT);
		
	pinMode(LOADER_CURRENT_PORT, INPUT);
	pinMode(VOLTAGE_PORT, INPUT);
	pinMode(FAN_PORT, OUTPUT);

	pinMode(BREACH_OPEN_PORT, OUTPUT);
	pinMode(BREACH_CLOSE_PORT, OUTPUT);
	pinMode(INJECTOR_PORT, OUTPUT);
	pinMode(RESERVED_RELAY_PORT, OUTPUT);
	
	pinMode(AMMO_SENSOR_PORT, INPUT);
	pinMode(FSS_PORT, INPUT);
	pinMode(RSS_PORT, INPUT);
	pinMode(INJ_LED_PORT, OUTPUT);
	pinMode(IGNITION_PORT, OUTPUT);
	pinMode(BLAST_SENSOR_PORT, INPUT);
	pinMode(BLAST_TRIGGER_RESET_PORT, OUTPUT);
	pinMode(SS_TRIGGER_RESET_PORT, OUTPUT);

	pinMode(RECEIVER_PRESSURE_PORT, INPUT);

	pinMode(BTN1_PORT, INPUT);
	pinMode(BTN2_PORT, INPUT);
	pinMode(BTN3_PORT, INPUT);
	pinMode(BTN4_PORT, INPUT);
	pinMode(BTN5_PORT, INPUT);
	pinMode(BTN6_PORT, INPUT);
}

float ArduinoWrapper::GetLoaderCurrent()
{
	auto curr = analogRead(LOADER_CURRENT_PORT);
	auto voltage = ANALOG_COEFFICIENT * double(curr);
	auto current = abs(CURRENT_MIDDLE_POINT - voltage) / CURRENT_COEFFICIENT;
	return current;
}

void ArduinoWrapper::LogFormat(char * message, ...)
{
	char buffer[128];
	va_list args = nullptr;
	va_start(args, message);
	vsnprintf(buffer, SCREEN_BUFFER_SIZE, message, args);
	va_end(args);

	Serial.println(buffer);
}

void ArduinoWrapper::LogFloatingPoint(double val)
{
	char buf[20];
	dtostrf(val, 7, 3, buf);
	Serial.println(buf);
}
