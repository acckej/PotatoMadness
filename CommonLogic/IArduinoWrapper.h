#pragma once
#include "TypeDefinitions.h"

class IArduinoWrapper  
{
public:
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

	virtual void SerialPrint(char* message);

	virtual void EngageLoader(bool forward, bool enable);
	virtual void EngageFan(bool enable);
	virtual double GetBatteryVoltage();
	virtual void EngageInjector(bool enable);
	virtual void EngageBreach(bool open, bool enable);
};

