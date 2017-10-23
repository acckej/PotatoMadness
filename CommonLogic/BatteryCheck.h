#pragma once
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "IHwCheck.h"
#include "Sensors.h"

class BatteryCheck : public IHwCheck
{
public:
	BatteryCheck(IArduinoWrapper* wrapper, TestScreen* screen, Sensors* sensors);
	
	CheckResult Check() override;

private:
	Sensors* _sensors;
};

