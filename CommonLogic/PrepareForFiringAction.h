#pragma once
#include "IAction.h"
#include "FiringController.h"
#include "Actuators.h"
#include "Sensors.h"

class PrepareForFiringAction : public IAction
{
public:
	PrepareForFiringAction(IArduinoWrapper* wrapper, FiringController* controller, Actuators* actuators, Sensors* sensors, IAction* nextAction);	

	void Reset() override;	
	bool CheckPreconditions() override;
	void StartAction() override;
	ActionState Execute() override;
	bool CheckPostConditions() override;
	void EndAction() override;
	int GetActionDuration() override;
	const char* GetActionName() override;
private:
	FiringController* _controller;
	Actuators * _actuators;
	Sensors* _sensors;
};

