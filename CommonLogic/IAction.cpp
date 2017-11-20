#include "IAction.h"


IAction::IAction(IArduinoWrapper* wrapper, IAction* nextAction)
{	
	_wrapper = wrapper;
	_errorCode = NoError;
	_nextAction = nextAction;
	_startTime = 0;
}

void IAction::Reset()
{
	_startTime = 0;
	_errorCode = NoError;	
}

const char * IAction::GetActionName()
{
	return "Default";
}

bool IAction::CheckPreconditions()
{
	return false;
}

void IAction::StartAction()
{
	_startTime = _wrapper->GetMilliseconds();
}

ActionState IAction::Execute()
{
	return Executing;
}

bool IAction::CheckPostConditions()
{
	return false;
}

void IAction::EndAction()
{
}

int IAction::GetActionDuration()
{
	return 0;
}

ErrorCodes IAction::GetErrorCode() const
{
	return _errorCode;
}

IAction * IAction::GetNextAction() const
{
	return _nextAction;
}

unsigned long IAction::GetStartTime() const
{
	return _startTime;
}

FiringState IAction::GetFiringState() const
{
	return _firingState;
}
