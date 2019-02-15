#include "Loader.h"
#include "Constants.h"
#include <math.h>


Loader::Loader(IArduinoWrapper* wrapper)
{
	_wrapper = wrapper;
}

void Loader::Forward() const
{
	_wrapper->DigitalWrite(LOADER_ENABLE_PORT, ARDUINO_LOW);
	/*_wrapper->DigitalWrite(LOADER_FWD_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(LOADER_REV_PORT, ARDUINO_LOW);*/
	_wrapper->DigitalWrite(LOADER_FWD_PORT, ARDUINO_HIGH);
	_wrapper->DigitalWrite(LOADER_REV_PORT, ARDUINO_HIGH);
}

void Loader::Reverse() const
{
	_wrapper->DigitalWrite(LOADER_ENABLE_PORT, ARDUINO_LOW);
	/*_wrapper->DigitalWrite(LOADER_FWD_PORT, ARDUINO_HIGH);
	_wrapper->DigitalWrite(LOADER_REV_PORT, ARDUINO_HIGH);*/
	_wrapper->DigitalWrite(LOADER_FWD_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(LOADER_REV_PORT, ARDUINO_LOW);
}

void Loader::Stop() const
{
	_wrapper->DigitalWrite(LOADER_ENABLE_PORT, ARDUINO_HIGH);
}

bool Loader::IsOverload() const
{
	auto current = GetCurrent();
	return current > LOADER_CURRENT_MAX;	
}

float Loader::GetCurrent() const
{
	auto curr = _wrapper->AnalogRead(LOADER_CURRENT_PORT);
	auto voltage = ANALOG_COEFFICIENT * double(curr);
	auto current = fabs(CURRENT_MIDDLE_POINT - voltage) / CURRENT_COEFFICIENT;
	return current;
}

bool Loader::NoAmmo() const
{
	auto result = _wrapper->DigitalRead(AMMO_SENSOR_PORT);
	return result == ARDUINO_LOW;
}

bool Loader::IsRevCheckOn() const
{
	auto result = _wrapper->AnalogRead(LDR_REV_CHECK_PORT);
	auto volt = ANALOG_COEFFICIENT * double(result);
	return volt <= LOADER_CHECKS_THRESHOLD;
}

bool Loader::IsFwCheckOn() const
{
	auto result = _wrapper->AnalogRead(LDR_FW_CHECK_PORT);
	auto volt = ANALOG_COEFFICIENT * double(result);
	return volt <= LOADER_CHECKS_THRESHOLD;
}





