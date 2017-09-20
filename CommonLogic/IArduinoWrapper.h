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
	virtual void LogFormat(char * message, ...);
	virtual void LogFloatingPoint(double val);

	virtual void SerialPrint(char* message);
	
	virtual double GetBatteryVoltage();
	
	virtual float GetAtmPressure();
	virtual float GetInternalTemp();
	virtual float GetExternalTemp();
	virtual float GetExternalHumidity();
	virtual float GetReceiverPressure();

	virtual void ResetDebouncingTriggers();	

	virtual unsigned long GetMilliseconds();

	virtual bool GetFss();
	virtual bool GetRss();

	virtual bool GetBlastSensorState();
};

