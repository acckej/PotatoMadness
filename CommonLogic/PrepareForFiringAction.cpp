#include "PrepareForFiringAction.h"
#include "Constants.h"
#include "Context.h"


PrepareForFiringAction::PrepareForFiringAction(
	IArduinoWrapper* wrapper, FiringController* controller, Actuators* actuators, Sensors* sensors, IAction* nextAction, FiringScreen* screen): IAction(wrapper, nextAction)
{
	_controller = controller;
	_actuators = actuators;
	_sensors = sensors;	
	_screen = screen;
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
	_actuators->TurnIngnitionOn();
	_firingState = Firing;
}

ActionState PrepareForFiringAction::Execute()
{
	if (_controller->GetErrorCode() != NoError)
	{
		_errorCode = _controller->GetErrorCode();
		return Error;
	}

	if (!_controller->GetFireFlag())
	{
		auto time = _wrapper->GetMilliseconds();

		if (time - _startTime > FIRING_TIMEOUT)
		{
			_errorCode = FiringTimeout;
			return Error;
		}
	}
	else
	{
		if (_firingState != Reloading)
		{
			auto speed = _controller->GetProjectileSpeed();
			_screen->PrintSpeed(speed);
			_firingState = Reloading;
			_controller->Reset();
		}

		if(Context::GetFiringSequenceMode() == SemiAuto)
		{
			return Context::GetButtonsController().IsButtonPressed(x3C) ? Completed : Waiting;
		}

		return Completed;
	}

	return Waiting;
}

void PrepareForFiringAction::EndAction()
{
	_actuators->TurnIgnitionOff();
	_controller->Reset();	
}

const char * PrepareForFiringAction::GetActionName()
{
	return "Firing prep.";
}
