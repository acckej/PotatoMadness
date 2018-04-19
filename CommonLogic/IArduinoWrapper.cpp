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

void IArduinoWrapper::Print(const char* message)
{		
}

void IArduinoWrapper::Print(double val, int digits)
{	
}

void IArduinoWrapper::PrintFormat(char * message, ...)
{
}

void IArduinoWrapper::PrintFormatBuffer(char* buffer, char* message, ...)
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

unsigned long IArduinoWrapper::GetMilliseconds()
{
	return 0;
}

