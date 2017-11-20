#pragma once
#include "IArduinoWrapper.h"
#include "IAction.h"
#include "FiringScreen.h"

class Sequenser
{
public:
	Sequenser(IArduinoWrapper* wrapper, IAction* startActionNormal, IAction* startActionForcedMixing, FiringScreen* screen);

	void Execute();

	void Stop() const;

	void Continue();

private:
	void HandleError(const char* message) const;

	IArduinoWrapper* _wrapper;
	IAction* _startActionNormal;
	IAction* _startActionForcedMixing;
	IAction* _currentAction;
	FiringScreen* _screen;
};

