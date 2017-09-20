#pragma once
#include "IAction.h"
#include "Configuration.h"
#include "Loader.h"

class LoaderForwardAction : public IAction
{
public:
	LoaderForwardAction(IArduinoWrapper* wrapper, Configuration* config, Loader* loader);
	void Reset() override;
	bool CheckPreconditions() override;
	void StartAction() override;
	ActionState Execute() override;
	bool CheckPostConditions() override;
	void EndAction() override;
	int GetActionDuration() override;	
private:
	void Stop() const;

	Configuration* _config;
	Loader* _loader;
};

