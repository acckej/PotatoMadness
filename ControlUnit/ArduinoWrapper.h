#pragma once
#include "IArduinoWrapper.h"

class ArduinoWrapper : public IArduinoWrapper 
{
public:	
	ArduinoWrapper();

	int DigitalRead(int port) override;
	void DigitalWrite(int port, int value) override;
	int AnalogRead(int port) override;
	void AnalogWrite(int port, int value) override;
	void Delay(unsigned long ms) override;
	void ClearScreen() override;
	void SetScreenCursor(char col, char row) override;
	void Print(const char msg[]) override;
	void Print(float val, int dp = 2) override;
	void SerialPrint(char* message) override;
};

