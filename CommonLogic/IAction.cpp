#include "IAction.h"


IAction::IAction(IArduinoWrapper* wrapper)
{
	_isCompleted = false;
	_wrapper = wrapper;
	_errorCode = NoError;
	_nextAction = nullptr;
}

bool IAction::IsCompleted() const
{
	return _isCompleted;
}

void IAction::Reset()
{
	_startTime = 0;
	_errorCode = NoError;
	_isCompleted = false;
}

bool IAction::CheckPreconditions()
{
	return false;
}

void IAction::StartAction()
{
	_startTime = _wrapper->GetMilliseconds();
}

bool IAction::Execute()
{
	return false;
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
