#pragma once
#include "IAction.h"
#include "FiringController.h"
#include "Actuators.h"
#include "Sensors.h"
#include "FiringScreen.h"

class PrepareForFiringAction : public IAction
{
public:
	PrepareForFiringAction(IArduinoWrapper* wrapper, FiringController* controller, Actuators* actuators, Sensors* sensors, IAction* nextAction, FiringScreen* screen);

	void Reset() override;	
	bool CheckPreconditions() override;
	void StartAction() override;
	ActionState Execute() override;	
	void EndAction() override;	
	const char* GetActionName() override;
private:
	FiringController* _controller;
	Actuators * _actuators;
	Sensors* _sensors;	
	FiringScreen* _screen;
};

