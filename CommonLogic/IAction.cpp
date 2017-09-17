#include "IAction.h"


IAction::IAction(IArduinoWrapper* wrapper)
{	
	_wrapper = wrapper;
	_errorCode = NoError;
	_nextAction = nullptr;
}

void IAction::Reset()
{
	_startTime = 0;
	_errorCode = NoError;	
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

bool IAction::IsError() const
{
	return _errorCode != NoError;
}

IAction * IAction::GetNextAction() const
{
	return _nextAction;
}

unsigned long IAction::GetStartTime()
{
	return _startTime;
}
