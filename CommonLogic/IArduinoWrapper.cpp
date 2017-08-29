#include "IArduinoWrapper.h"

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

void IArduinoWrapper::SerialPrint(char * message)
{
}
