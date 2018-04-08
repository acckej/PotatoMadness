#pragma once
#include "IArduinoWrapper.h"
#include "Frame.h"

class ArduinoFrameStub : public IArduinoWrapper
{
public:
	ArduinoFrameStub(Frame * frame);	

	void Init() override;
	int DigitalRead(unsigned port) override;
	void DigitalWrite(unsigned port, int value) override;
	int AnalogRead(unsigned port) override;
	void AnalogWrite(unsigned port, int value) override;
	void Delay(unsigned long delay) override;
	void ClearScreen() override;
	void SetScreenCursor(char col, char row) override;
	void Print(const char[]) override;
	void Print(double val, int digits) override;
	void PrintFormat(char* message, ...) override;
	void PrintFormatBuffer(char* buffer, char* message, ...) override;
	void LogFormat(char* message, ...) override;
	void LogFloatingPoint(double val) override;
	void SerialPrint(char* message) override;
	float GetAtmPressure() override;
	float GetInternalTemp() override;
	float GetExternalTemp() override;
	float GetExternalHumidity() override;
	unsigned long GetMilliseconds() override;

	void IncrementFrame();
private:
	Frame * _frame;
};

