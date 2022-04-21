#pragma once
#include "IHwCheck.h"
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "Context.h"

class IgnitionCheck : public IHwCheck
{
public:
	IgnitionCheck(IArduinoWrapper* wrapper, TestScreen* screen, Loader* loader, Actuators* actuators);

	CheckResult Check() override;
private:
	void Stop() const;
	CheckResult CheckCurrent(char messageLine);

	Loader* _loader;
	Actuators* _actuators;
	bool _isFwd;
};

