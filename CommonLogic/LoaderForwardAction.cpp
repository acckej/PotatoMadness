#include "LoaderForwardAction.h"
#include "Constants.h"


LoaderForwardAction::LoaderForwardAction(IArduinoWrapper* wrapper, IConfiguration* config, Loader* loader, Actuators* actuators, Sensors* sensors, IAction* nextAction) : IAction(wrapper, nextAction)
{
	_config = config;
	_loader = loader;
	_actuators = actuators;
	_sensors = sensors;	
	_openStart = false;
}

void LoaderForwardAction::Reset()
{
	IAction::Reset();	
	_openStart = false;
}

bool LoaderForwardAction::CheckPreconditions()
{
	if(!_loader->IsFwCheckOn() || _loader->IsRevCheckOn())
	{
		if(!_loader->IsFwCheckOn() && _loader->IsRevCheckOn())
		{
			_openStart = true;
		}
		else
		{
			_errorCode = IncorrectLoaderPositionFwd;
			return false;
		}
	}	

	auto voltage = _sensors->GetBatteryVoltage();

	if(voltage < LOW_VOLTAGE)
	{
		_errorCode = LowVoltage;
		return false;
	}

	return true;
}

void LoaderForwardAction::StartAction()
{
	IAction::StartAction();

	_actuators->OpenBreech();
	_actuators->TurnFanOn();
	_loader->Forward();
	_firingState = Reversed;
}

void LoaderForwardAction::Stop() const
{
	_actuators->TurnFanOff();
	_loader->Stop();
}

ActionState LoaderForwardAction::Execute()
{
	if(_loader->IsOverload())
	{
		_errorCode = LoaderOverload;
		Stop();
		return Error;
	}

	_firingState = RevFront;

	if (_loader->IsRevCheckOn())
	{
		if (!_openStart)
		{
			_actuators->TurnFanOff();
			_firingState = Front;
			return Completed;
		}

		if (!_actuators->FanOn())
		{
			_actuators->TurnFanOn();
		}
	}

	auto time = _wrapper->GetMilliseconds();

	auto duration = time - _startTime;

	if(duration > LOADER_FORWARD_TIME)
	{
		Stop();
		_errorCode = LoaderForwardTimeout;
		return Error;
	}

	if(duration > _config ->GetLoaderForwardFanTime() && _actuators->FanOn())
	{
		_actuators->TurnFanOff();

		if(_openStart)
		{
			return Completed;
		}
	}

	return Executing;
}

void LoaderForwardAction::EndAction()
{
	Stop();	
	_openStart = false;
}

const char * LoaderForwardAction::GetActionName()
{
	return "Ldr. fwd.";
}


