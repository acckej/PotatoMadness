#pragma once
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "IHwCheck.h"

class BatteryCheck : public IHwCheck
{
public:
	BatteryCheck(IArduinoWrapper* wrapper, TestScreen* screen);
	
	CheckResult Check() override;
};

