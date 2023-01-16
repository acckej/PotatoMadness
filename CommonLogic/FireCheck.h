#pragma once
#include "IHwCheck.h"
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "Context.h"
#include "Injector.h"

class FireCheck : public IHwCheck
{
public:
	FireCheck(IArduinoWrapper* wrapper, 
		TestScreen* screen, 
		Loader* loader, 
		Actuators* actuators, 
		Sensors* sensors, 
		ButtonsController* buttons, 
		Injector* injector);

	CheckResult Check() override;

	static void BlastSensorHandler();

	static volatile bool _blast;

private:
	void ShowSpeed();	
	
	Actuators* _actuators;
	Sensors* _sensors; 
	ButtonsController* _buttons;
	Injector* _injector;

	bool _breechOpen;
	bool _isFwCycle;
	bool _isRevCycle;
	bool _injecting;
	bool _speedRequest;
	bool _measOn;
	bool _measRequest;

	int _fwCycleCounter;
	int _revCycleCounter;	
};

