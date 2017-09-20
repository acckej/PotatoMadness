#include "PrepareForFiringAction.h"
#include "Constants.h"


PrepareForFiringAction::PrepareForFiringAction(IArduinoWrapper* wrapper, FiringController* controller, Actuators* actuators): IAction(wrapper)
{
	_controller = controller;
	_actuators = actuators;
}

void PrepareForFiringAction::Reset()
{
	IAction::Reset();
}

bool PrepareForFiringAction::CheckPreconditions()
{
	auto voltage = _wrapper->GetBatteryVoltage();

	if (voltage < LOW_VOLTAGE)
	{
		_errorCode = LowVoltage;
		return false;
	}

	_wrapper->ResetDebouncingTriggers();

	if (_wrapper->GetRss() || _wrapper->GetFss() || _wrapper->GetBlastSensorState())
	{
		_errorCode = IncorrectShotSensorsState;
		return false;
	}

	return true;
}

void PrepareForFiringAction::StartAction()
{
	IAction::StartAction();
	
	_controller->Reset();
	_actuators->IngnitionOn();
}

ActionState PrepareForFiringAction::Execute()
{
	auto time = _wrapper->GetMilliseconds();

	if(time - _startTime > FIRING_TIMEOUT)
	{
		_errorCode = FiringTimeout;
		return Error;
	}

	if(_controller->GetErrorCode() != NoError)
	{
		_errorCode = _controller->GetErrorCode();
		return Error;
	}

	if(_controller->GetFireFlag())
	{
		//update screen
		_controller->Reset();
		return Completed;
	}

	return Waiting;
}

bool PrepareForFiringAction::CheckPostConditions()
{
	return false;
}

void PrepareForFiringAction::EndAction()
{
	_actuators->IgnitionOff();
}

int PrepareForFiringAction::GetActionDuration()
{
	return 0;
}
