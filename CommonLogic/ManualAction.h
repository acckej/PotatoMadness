#pragma once
#include "IAction.h"
#include "Loader.h"
#include "Actuators.h"
#include "Sensors.h"
#include "Context.h"

#define BUTTONS_DELAY 500

class ManualScreen;

class ManualAction :
	public IAction
{
public:
	ManualAction(IArduinoWrapper* wrapper, Loader* loader, Actuators* actuators, Sensors* sensors, ManualScreen* screen);
	~ManualAction();

	ActionState Execute() override;

	const char* GetActionName() override;
private:
	void CheckLoaderButtons();
	void CheckLoaderState();
	void CheckBreechButton();	
	void CheckFanButtons();
	void CheckInjectorButton() const;
	void CheckIgnitionButton();
	
	long _fanStarted;
	long _loaderStarted;
	long _ignitionStarted;
	long _breechStarted;
	
	Loader* _loader;
	Actuators* _actuators;
	Sensors* _sensors;	
	ManualScreen* _screen;
};

