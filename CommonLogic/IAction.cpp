#include "IAction.h"


IAction::IAction(IArduinoWrapper* wrapper, IAction* nextAction)
{	
	_wrapper = wrapper;
	_errorCode = NoError;
	_nextAction = nextAction;
	_startTime = 0;
	_firingState = Undefined;
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

void IAction::EndAction()
{
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
