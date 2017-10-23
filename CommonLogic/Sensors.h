#pragma once

#include "IArduinoWrapper.h"

class Sensors
{
public:
	Sensors(IArduinoWrapper* wrapper);

	double GetBatteryVoltage() const;	
	float GetReceiverPressure() const;
	void ResetDebouncingTriggers() const;

	bool GetFss() const;
	bool GetRss() const;

	bool GetBlastSensorState() const;
	
private:
	IArduinoWrapper* _wrapper;
};

