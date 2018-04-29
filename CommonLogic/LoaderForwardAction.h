#pragma once
#include "IAction.h"
#include "Configuration.h"
#include "Loader.h"
#include "Actuators.h"
#include "Sensors.h"

class LoaderForwardAction : public IAction
{
public:
	LoaderForwardAction(IArduinoWrapper* wrapper, IConfiguration* config, Loader* loader, Actuators* actuators, Sensors* sensors, IAction* nextAction);
	void Reset() override;
	bool CheckPreconditions() override;
	void StartAction() override;
	ActionState Execute() override;	
	void EndAction() override;	
	const char* GetActionName() override;
private:
	void Stop() const;
		
	IConfiguration* _config;
	Loader* _loader;
	Actuators* _actuators;
	Sensors* _sensors;
};

