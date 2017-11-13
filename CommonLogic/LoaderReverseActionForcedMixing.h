#pragma once
#include "IAction.h"
#include "Configuration.h"
#include "Injector.h"
#include "Loader.h"
#include "Actuators.h"
#include "Sensors.h"

#define FAN_SPINUP_TIME 1000

class LoaderReverseActionForcedMixing : public IAction
{
public:
	LoaderReverseActionForcedMixing(IArduinoWrapper* wrapper, Configuration* config, Injector* injector, Loader* loader, Actuators* actuators, Sensors* sensors, IAction* nextAction);

	void Reset() override;
	bool CheckPreconditions() override;
	void StartAction() override;
	ActionState Execute() override;
	bool CheckPostConditions() override;
	void EndAction() override;
	int GetActionDuration() override;
private:
	Configuration* _config;
	Injector* _injector;
	Loader* _loader;
	Actuators* _actuators;
	Sensors* _sensors;

	unsigned long _injectionStart;
	bool _isInjection;
	bool _injected;
	bool _mixed;
	unsigned long _breachClosingStart;

	void Stop() const;
};

