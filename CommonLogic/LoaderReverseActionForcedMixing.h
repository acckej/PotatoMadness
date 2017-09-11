#pragma once
#include "IAction.h"

class LoaderReverseActionForcedMixing : public IAction
{
public:
	LoaderReverseActionForcedMixing(IArduinoWrapper* wrapper);

	void Reset() override;
	bool CheckPreconditions() override;
	void StartAction() override;
	bool Execute() override;
	bool CheckPostConditions() override;
	void EndAction() override;
	int GetActionDuration() override;
};

