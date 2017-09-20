#pragma once
#include "IAction.h"
#include "FiringController.h"
#include "Actuators.h"

class PrepareForFiringAction : IAction
{
public:
	PrepareForFiringAction(IArduinoWrapper* wrapper, FiringController* controller, Actuators* actuators);

	void Reset() override;
	bool CheckPreconditions() override;
	void StartAction() override;
	ActionState Execute() override;
	bool CheckPostConditions() override;
	void EndAction() override;
	int GetActionDuration() override;
private:
	FiringController* _controller;
	Actuators * _actuators;
};

