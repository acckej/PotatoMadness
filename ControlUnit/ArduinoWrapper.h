#pragma once
#include "IArduinoWrapper.h"

class ArduinoWrapper : public IArduinoWrapper 
{
public:	
	ArduinoWrapper();

	int DigitalRead(unsigned int port) override;
	void DigitalWrite(unsigned int port, int value) override;
	int AnalogRead(unsigned int port) override;
	void AnalogWrite(unsigned int port, int value) override;
	void Delay(unsigned long ms) override;
	void ClearScreen() override;
	void SetScreenCursor(char col, char row) override;
	void Print(const char msg[]) override;
	void Print(double val, int dp = 2) override;
	void SerialPrint(char* message) override;
	void PrintFormat(char* message, ...) override;
	void EngageLoader(bool forward, bool enable) override;
	void EngageFan(bool enable) override;
	double GetBatteryVoltage() override;
	void EngageInjector(bool enable) override;
	void EngageBreach(bool open, bool enable) override;
	float GetAtmPressure() override;
	float GetInternalTemp() override;
	float GetExternalTemp() override;
	float GetExternalHumidity() override;
	float GetReceiverPressure() override;
	void ResetDebouncingTriggers() override;
	bool GetAmmoSensorState() override;
	void EngageIngnition(bool enabled) override;
	void EngageInjectorDiode(bool enabled) override;
	void Init() override;
	float GetLoaderCurrent() override;
	void LogFormat(char* message, ...) override;
	void LogFloatingPoint(double val) override;
	bool IsRevCheckOn() override;
	bool IsFwCheckOn() override;
	unsigned long GetMilliseconds() override;
	bool GetFss() override;
	bool GetRss() override;
	bool GetBlastSensorState() override;
};

