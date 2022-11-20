#include "ArduinoWrapper.h"
#include <Arduino.h>
#include "Constants.h"
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>
#include "CalculationConstants.h"
#include "EEPROM.h"
#include "TypeDefinitions.h"

SoftwareSerial g_link(MASTER_SERIAL_RX, MASTER_SERIAL_TX); // Rx, Tx
LiquidCrystal_I2C lcd(0x27, 20, 4); //0x3f
#define DHTTYPE DHT22 //DHT11

Adafruit_BMP280 atm_p_sens;
DHT dht(TEMP_HUM_SENSOR_PORT, DHTTYPE);

ArduinoWrapper::ArduinoWrapper()
= default;

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

void ArduinoWrapper::Print(double val, int dp)
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

	lcd.print(buffer);
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
	return atm_p_sens.readPressure() / ATM_PRESSURE_COEF * KILO;	
}

float ArduinoWrapper::GetInternalTemp()
{	
	return atm_p_sens.readTemperature();
}

float ArduinoWrapper::GetExternalTemp()
{
	const auto t = dht.readTemperature();
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
	pinMode(HEATER_PORT, OUTPUT);
	pinMode(HEATER_SENSOR_PORT, INPUT);
		
	pinMode(BLAST_SENSOR_PORT, INPUT);

	pinMode(INJ_LED_PORT, OUTPUT);
	pinMode(IGNITION_PORT, OUTPUT);
	
	pinMode(BLAST_TRIGGER_RESET_PORT, OUTPUT);
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

	pinMode(CYCLE_VALVE_PORT_ONE, OUTPUT);
	pinMode(CYCLE_VALVE_PORT_TWO, OUTPUT);

	dht.begin();	
	atm_p_sens.begin(BAROMETER_ADDRESS);	
	g_link.begin(SERIAL_SPEED);
}

void ArduinoWrapper::LogFormat(char * message, ...)
{
	char buffer[LOG_BUFSIZE];
	va_list args = nullptr;
	va_start(args, message);
	vsnprintf(buffer, LOG_BUFSIZE, message, args);
	va_end(args);

	Serial.println(buffer);
}

void ArduinoWrapper::LogFloatingPoint(double val)
{
	char buf[FLOATING_POINT_BUFSIZE];
	dtostrf(val, 7, 3, buf);
	Serial.println(buf);
}

unsigned long ArduinoWrapper::GetMilliseconds()
{
	return millis();
}

unsigned long ArduinoWrapper::GetMicroseconds()
{
	return micros();
}

double ArduinoWrapper::GetSpeed()
{
	g_link.write(GET_SPEED_COMMAND);
	g_link.flush();
	delay(MEAS_UNIT_RESPONSE_DELAY);
	unsigned char buf[sizeof(double)];

	auto bytesRead = 0;

	while (g_link.available())
	{
		auto ch = static_cast<unsigned char>(g_link.read());
		buf[bytesRead] = ch;
		bytesRead++;

		if(bytesRead >= sizeof(double))
		{
			const auto result = *reinterpret_cast<ArduinoDouble*>(buf);
			return result;
		}
	}

	return NAN;
}

void ArduinoWrapper::StartMeasuring()
{
	g_link.write(START_MEAS_COMMAND);
	g_link.flush();
}

void ArduinoWrapper::MeasuringUnitStby()
{
	g_link.write(MEAS_STBY_COMMAND);
	g_link.flush();
}

void ArduinoWrapper::SetTestSpeed()
{
	g_link.write(TEST_SPEED_COMMAND);
	g_link.flush();
}

unsigned char ArduinoWrapper::ReadFromEeprom(short index)
{
	return EEPROM.read(index);
}

void ArduinoWrapper::WriteToEeprom(short index, unsigned char value)
{
	EEPROM.write(index, value);
}


