#pragma once
#include "IAction.h"
#include "Configuration.h"

class LoaderForwardAction : public IAction
{
public:
	LoaderForwardAction(IArduinoWrapper* wrapper, Configuration* config);
	void Reset() override;
	bool CheckPreconditions() override;
	void StartAction() override;
	bool Execute() override;
	bool CheckPostConditions() override;
	void EndAction() override;
	int GetActionDuration() override;	
private:
	void Stop() const;

	Configuration* _config;
};

