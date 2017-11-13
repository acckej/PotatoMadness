#pragma once
#include "IArduinoWrapper.h"
#include "IAction.h"

class Sequenser
{
public:
	Sequenser(IArduinoWrapper* wrapper, IAction* startActionNormal, IAction* startActionForcedMixing);

	void Execute();

private:
	IArduinoWrapper* _wrapper;
	IAction* _startActionNormal;
	IAction* _startActionForcedMixing;
	IAction* _currentAction;
};

