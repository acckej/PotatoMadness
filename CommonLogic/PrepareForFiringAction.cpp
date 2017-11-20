#include "PrepareForFiringAction.h"
#include "Constants.h"


PrepareForFiringAction::PrepareForFiringAction(
	IArduinoWrapper* wrapper, FiringController* controller, Actuators* actuators, Sensors* sensors, IAction* nextAction): IAction(wrapper, nextAction)
{
	_controller = controller;
	_actuators = actuators;
	_sensors = sensors;
}

void PrepareForFiringAction::Reset()
{
	IAction::Reset();
}

bool PrepareForFiringAction::CheckPreconditions()
{
	auto voltage = _sensors->GetBatteryVoltage();

	if (voltage < LOW_VOLTAGE)
	{
		_errorCode = LowVoltage;
		return false;
	}

	_sensors->ResetDebouncingTriggers();

	if (_sensors->GetRss() || _sensors->GetFss() || _sensors->GetBlastSensorState())
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
	_firingState = Firing;
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
		_firingState = Reloading;
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

const char * PrepareForFiringAction::GetActionName()
{
	return "Firing prep.";
}
