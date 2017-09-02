#include "IArduinoWrapper.h"

void IArduinoWrapper::Init()
{
}

int IArduinoWrapper::DigitalRead(unsigned int port)
{
	return int();
}

void IArduinoWrapper::DigitalWrite(unsigned int port, int value)
{
}

int IArduinoWrapper::AnalogRead(unsigned int port)
{
	return double();
}

void IArduinoWrapper::AnalogWrite(unsigned int port, int value)
{
}

void IArduinoWrapper::Delay(unsigned long delay)
{
}

void IArduinoWrapper::ClearScreen()
{
}

void IArduinoWrapper::SetScreenCursor(char col, char row)
{
}

void IArduinoWrapper::Print(const char[])
{	
}

void IArduinoWrapper::Print(double val, int digits)
{	
}

void IArduinoWrapper::PrintFormat(char * message, ...)
{
}

void IArduinoWrapper::LogFormat(char * message, ...)
{
}

void IArduinoWrapper::LogFloatingPoint(double val)
{
}

void IArduinoWrapper::SerialPrint(char * message)
{
}

void IArduinoWrapper::EngageLoader(bool forward, bool enable)
{
}

void IArduinoWrapper::EngageFan(bool enable)
{
}

double IArduinoWrapper::GetBatteryVoltage()
{
	return 0.0;
}

void IArduinoWrapper::EngageInjector(bool enable)
{
}

void IArduinoWrapper::EngageBreach(bool open, bool enable)
{
}

float IArduinoWrapper::GetAtmPressure()
{
	return 0.0f;
}

float IArduinoWrapper::GetInternalTemp()
{
	return 0.0f;
}

float IArduinoWrapper::GetExternalTemp()
{
	return 0.0f;
}

float IArduinoWrapper::GetExternalHumidity()
{
	return 0.0f;
}

float IArduinoWrapper::GetReceiverPressure()
{
	return 0.0f;
}

float IArduinoWrapper::GetLoaderCurrent()
{
	return 0.0f;
}

void IArduinoWrapper::ResetDebouncingTriggers()
{
}

bool IArduinoWrapper::GetAmmoSensorState()
{
	return false;
}

void IArduinoWrapper::EngageIngnition(bool enabled)
{
}

void IArduinoWrapper::EngageInjectorDiode(bool enabled)
{
}
