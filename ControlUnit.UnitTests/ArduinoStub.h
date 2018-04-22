#pragma once
#include "IArduinoWrapper.h"


typedef int(*DigitalReadDelegate)(int port);
typedef void(*DigitalWriteDelegate)(int port, int value);
typedef int(*AnalogReadDelegate)(int port);

class ArduinoStub : public IArduinoWrapper 
{
public:	
	ArduinoStub(DigitalReadDelegate digRead = nullptr, DigitalWriteDelegate digWrite = nullptr, AnalogReadDelegate anRead = nullptr);

	int DigitalRead(unsigned int port) override;
	void DigitalWrite(unsigned int port, int value) override;
	int AnalogRead(unsigned int port) override;
	void AnalogWrite(unsigned int port, int value) override;
	void Delay(unsigned long delay) override;
	void ClearScreen() override;
	void SetScreenCursor(char col, char row) override;
	void Print(const char msg[]) override;
	void Print(double val, int) override;
	void SerialPrint(char* message) override;
	void PrintFormat(char* message, ...) override;		
	
	float GetAtmPressure() override;
	float GetInternalTemp() override;
	float GetExternalTemp() override;
	float GetExternalHumidity() override;
	void PrintFormatBuffer(char* buffer, char* message, ...) override;
	unsigned long GetMilliseconds() override;
private:
	DigitalReadDelegate _readDelegate;
	DigitalWriteDelegate _writeDelegate;
	AnalogReadDelegate _analogReadDelegate;
};

