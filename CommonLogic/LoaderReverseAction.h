#pragma once
#include "IAction.h"
#include "Injector.h"
#include "Loader.h"
#include "Actuators.h"
#include "Sensors.h"

#define BREACH_ENGAGE_TIME 3000

class LoaderReverseAction : public IAction
{
public:
	LoaderReverseAction(IArduinoWrapper* wrapper, Injector* injector, Loader* loader, Actuators* actuators, Sensors* sensors, IAction* nextAction);

	void Reset() override;
	bool CheckPreconditions() override;
	void StartAction() override;
	ActionState Execute() override;
	bool CheckPostConditions() override;
	void EndAction() override;
	int GetActionDuration() override;	
private:
	void Stop() const;

	Injector* _injector;	
	Loader* _loader;
	Actuators* _actuators;
	Sensors* _sensors;
};

