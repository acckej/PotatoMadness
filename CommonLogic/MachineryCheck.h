#pragma once
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "IHwCheck.h"
#include "Constants.h"

class MachineryCheck : public IHwCheck
{
public:
	MachineryCheck(IArduinoWrapper* wrapper, TestScreen* screen);

	CheckResult Check() override;
private:
	bool _fan;
	bool _injector;
	bool _breachOpen;
	bool _breachClose;
};

