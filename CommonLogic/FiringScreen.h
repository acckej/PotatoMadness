#pragma once
#include "IArduinoWrapper.h"
#include "ScreenBase.h"

class FiringScreen : public ScreenBase 
{
public:
	FiringScreen(IArduinoWrapper* wrapper);

	void PrintStatus(char row, const char* message);
	void PrintVoltage(float voltage);
	void PrintTemperature(float temperature);
	void PrintLoaderCurrent(float current);
	void PrintSpeed(float speed);
	void PrintHumidity(float humidity);
	void PrintPressure(float pressure);
};

