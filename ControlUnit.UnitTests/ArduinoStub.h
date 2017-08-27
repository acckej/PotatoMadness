#pragma once
#include "IArduinoWrapper.h"

class ArduinoStub : public IArduinoWrapper 
{
public:	
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
};

