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

	static void FssOn();
	static void RssOn();
	static void BlastOn();

private:
	void Stop() const;
	CheckResult CheckCurrent(char messageLine);
	
	Loader* _loader;
	Actuators* _actuators;
	Sensors* _sensors; 
	ButtonsController* _buttons;
	Injector* _injector;

	bool _breechOpen;
	bool _isFwCycle;
	bool _isRevCycle;
	bool _injecting;

	int _fwCycleCounter;
	int _revCycleCounter;

	static IArduinoWrapper* _staticWrapper;
	static volatile unsigned long _millis;
	static volatile bool _blastEngaged;
	static volatile bool _fssOn;
	static volatile bool _rssOn;
};

