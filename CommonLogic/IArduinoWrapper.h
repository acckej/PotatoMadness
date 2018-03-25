#pragma once
#include "TypeDefinitions.h"

class IArduinoWrapper  
{
public:
	virtual void Init();

	virtual int DigitalRead(unsigned int port);
	virtual void DigitalWrite(unsigned int port, int value);
	
	virtual int AnalogRead(unsigned int port);
	virtual void AnalogWrite(unsigned int port, int value);

	virtual void Delay(unsigned long delay);

	virtual void ClearScreen();

	virtual void SetScreenCursor(char col, char row);
	virtual void Print(const char[]);

	virtual void Print(double val, int digits);

	virtual void PrintFormat(char* message, ...);
	virtual void PrintFormatBuffer(char* buffer, char* message, ...);
	virtual void LogFormat(char * message, ...);
	virtual void LogFloatingPoint(double val);

	virtual void SerialPrint(char* message);
	
	virtual float GetAtmPressure();
	virtual float GetInternalTemp();
	virtual float GetExternalTemp();
	virtual float GetExternalHumidity();

	virtual unsigned long GetMilliseconds();	
};

