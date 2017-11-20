#pragma once
#include "IArduinoWrapper.h"
#include "ScreenBase.h"

class FiringScreen : public ScreenBase 
{
public:
	FiringScreen(IArduinoWrapper* wrapper);

	void PrintStatus(char row, const char* message) const;
	void PrintVoltage(float voltage) const;
	void PrintTemperature(float temperature) const;
	void PrintLoaderCurrent(float current) const;
	void PrintSpeed(float speed) const;
	void PrintHumidity(float humidity) const;
	void PrintPressure(float pressure) const;
};

