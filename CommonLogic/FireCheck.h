#pragma once
#include "IHwCheck.h"
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "Context.h"
#include "Injector.h"

class FireCheck : public IHwCheck
{
public:
	FireCheck(IArduinoWrapper* wrapper, TestScreen* screen, Loader* loader, Actuators* actuators, Sensors* sensors, ButtonsController* buttons, Injector* injector);

	CheckResult Check() override;
private:
	void Stop() const;
	CheckResult CheckCurrent(char messageLine);

	Loader* _loader;
	Actuators* _actuators;
	Sensors* _sensors; ButtonsController* _buttons;
	Injector* _injector;

	bool _breechOpen;
	bool _isFwCycle;
	bool _isRevCycle;

	int _fwCycleCounter;
	int _revCycleCounter;
};

