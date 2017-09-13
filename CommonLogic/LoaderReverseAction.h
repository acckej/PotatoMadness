#pragma once
#include "IAction.h"
#include "Injector.h"

#define BREACH_ENGAGE_TIME 3000

class LoaderReverseAction : public IAction
{
public:
	LoaderReverseAction(IArduinoWrapper* wrapper, Injector* injector);

	void Reset() override;
	bool CheckPreconditions() override;
	void StartAction() override;
	bool Execute() override;
	bool CheckPostConditions() override;
	void EndAction() override;
	int GetActionDuration() override;	
private:
	void Stop() const;

	Injector* _injector;	
};

