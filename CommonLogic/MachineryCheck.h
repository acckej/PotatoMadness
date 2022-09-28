#pragma once
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "IHwCheck.h"
#include "Constants.h"
#include "Actuators.h"

class MachineryCheck : public IHwCheck
{
public:
	MachineryCheck(IArduinoWrapper* wrapper, TestScreen* screen, Actuators* actuators);

	CheckResult Check() override;
private:
	bool _fan;
	bool _injector;
	bool _breechOpen;
	bool _breechClose;
	bool _cycleInternal;
	Actuators* _actuators;
};

