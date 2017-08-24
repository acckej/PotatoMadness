#include "IAction.h"



IAction::IAction()
{
}


IAction::~IAction()
{
}

bool IAction::IsAsync()
{
	return false;
}

bool IAction::IsCompleted()
{
	return false;
}

void IAction::Reset()
{
}

bool IAction::CheckPreconditions()
{
	return false;
}

void IAction::StartAction()
{
}

bool IAction::IsWaiting()
{
	return false;
}

bool IAction::CheckRunningCondition()
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
