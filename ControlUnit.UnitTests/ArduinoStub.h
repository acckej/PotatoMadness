#pragma once
#include "IArduinoWrapper.h"


typedef int(*DigitalReadDelegate)(int port);
typedef void(*DigitalWriteDelegate)(int port, int value);
typedef int(*AnalogReadDelegate)(int port);

class ArduinoStub : public IArduinoWrapper 
{
public:	
	ArduinoStub(DigitalReadDelegate digRead = nullptr, DigitalWriteDelegate digWrite = nullptr, AnalogReadDelegate anRead = nullptr);

	int DigitalRead(int port) override;
	void DigitalWrite(int port, int value) override;
	int AnalogRead(int port) override;
	void AnalogWrite(int port, int value) override;
	void Delay(unsigned long delay) override;
	void ClearScreen() override;
	void SetScreenCursor(char col, char row) override;
	void Print(const char msg[]) override;
	void Print(float val, int) override;
	void SerialPrint(char* message) override;
	void PrintFormat(char* message, ...) override;
private:
	DigitalReadDelegate _readDelegate;
	DigitalWriteDelegate _writeDelegate;
	AnalogReadDelegate _analogReadDelegate;
};

