#include "IArduinoWrapper.h"

ArduinoInt IArduinoWrapper::DigitalRead(ArduinoUInt port)
{
	return ArduinoInt();
}

void IArduinoWrapper::DigitalWrite(ArduinoUInt port, ArduinoInt value)
{
}

ArduinoInt IArduinoWrapper::AnalogRead(ArduinoUInt port)
{
	return ArduinoDouble();
}

void IArduinoWrapper::AnalogWrite(ArduinoUInt port, ArduinoInt value)
{
}

void IArduinoWrapper::Delay(ArduinoULong delay)
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

void IArduinoWrapper::Print(ArduinoDouble val, ArduinoInt = 2)
{	
}

void IArduinoWrapper::SerialPrint(char * message)
{
}
