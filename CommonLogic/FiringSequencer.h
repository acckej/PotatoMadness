#pragma once
#include "IArduinoWrapper.h"
#include "IAction.h"
#include "FiringScreen.h"

class FiringSequencer
{
public:	
	FiringSequencer(IArduinoWrapper* wrapper, IAction* startActionNormal, IAction* startActionForcedMixing, FiringScreen* screen);
		
	ActionState Execute();

	void Stop();

	bool Continue();

private:
	void HandleError(const char* message) const;

	IArduinoWrapper* _wrapper;
	IAction* _startActionNormal;
	IAction* _startActionForcedMixing;
	IAction* _currentAction;
	FiringScreen* _screen;
};

