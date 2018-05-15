#include "ArduinoWrapper.h"
#include <Arduino.h>
#include "Constants.h"
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>


LiquidCrystal_I2C lcd(0x27, 20, 4); //0x3f
#define DHTTYPE DHT11  

Adafruit_BMP280 atmPSens;
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

void ArduinoWrapper::PrintFormatBuffer(char * buffer, char * message, ...)
{	
	va_list args = nullptr;
	va_start(args, message);
	vsnprintf(buffer, SCREEN_BUFFER_SIZE, message, args);
	va_end(args);
}

float ArduinoWrapper::GetAtmPressure()
{
	return atmPSens.readPressure() / ATM_PRESSURE_COEF;
}

float ArduinoWrapper::GetInternalTemp()
{	
	return atmPSens.readTemperature();
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
		
	pinMode(FSS_PORT, INPUT);
	pinMode(RSS_PORT, INPUT);
	pinMode(BLAST_SENSOR_PORT, INPUT);

	pinMode(INJ_LED_PORT, OUTPUT);
	pinMode(IGNITION_PORT, OUTPUT);
	
	pinMode(BLAST_TRIGGER_RESET_PORT, OUTPUT);
	pinMode(SS_TRIGGER_RESET_PORT, OUTPUT);

	pinMode(RECEIVER_PRESSURE_PORT, INPUT);

	pinMode(AMMO_SENSOR_PORT, INPUT);
	pinMode(BTN1_PORT, INPUT);
	pinMode(BTN2_PORT, INPUT);
	pinMode(BTN3_PORT, INPUT);
	pinMode(BTN4_PORT, INPUT);
	pinMode(BTN5_PORT, INPUT);
	pinMode(BTN6_PORT, INPUT);
	pinMode(LDR_FW_CHECK_PORT, INPUT);
	pinMode(LDR_REV_CHECK_PORT, INPUT);

	atmPSens.begin(BAROMETER_ADDRESS);	
}

void ArduinoWrapper::LogFormat(char * message, ...)
{
	char buffer[128];
	va_list args = nullptr;
	va_start(args, message);
	vsnprintf(buffer, 128, message, args);
	va_end(args);

	Serial.println(buffer);
}

void ArduinoWrapper::LogFloatingPoint(double val)
{
	char buf[20];
	dtostrf(val, 7, 3, buf);
	Serial.println(buf);
}

unsigned long ArduinoWrapper::GetMilliseconds()
{
	return millis();
}


