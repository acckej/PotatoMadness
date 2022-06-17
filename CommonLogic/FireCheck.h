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

	static void FssOnOrd();
	static void RssOnOrd();
	static void BlastOnOrd();

private:
	void Stop() const;
	CheckResult CheckCurrent(char messageLine);
	void InitSpeedCalculation();
	
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
	static volatile unsigned long _micros;
	static volatile unsigned long _rMicros;
	static volatile bool _blastEngaged;
	static volatile bool _fssOn;
	static volatile bool _rssOn;
	static volatile short _order;
	static volatile short _digit;
};

