#include "LoaderForwardAction.h"
#include "Constants.h"


LoaderForwardAction::LoaderForwardAction(IArduinoWrapper* wrapper, Configuration* config, Loader* loader): IAction(wrapper)
{
	_config = config;
	_loader = loader;
}

void LoaderForwardAction::Reset()
{
	IAction::Reset();	
}

bool LoaderForwardAction::CheckPreconditions()
{
	if(!_loader->IsFwCheckOn() || _loader->IsRevCheckOn())
	{
		_errorCode = IncorrectLoaderPositionFwd;
		return false;
	}

	auto pressure = _wrapper->GetReceiverPressure();

	if(pressure < RECEIVER_PRESSURE_MIN)
	{
		_errorCode = ReceiverPressureLow;
		return false;
	}

	if (pressure > RECEIVER_PRESSURE_MAX)
	{
		_errorCode = ReceiverPressureHigh;
		return false;
	}

	auto voltage = _wrapper->GetBatteryVoltage();

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

	_wrapper->EngageBreach(true, true);
	_wrapper->EngageFan(true);
	_loader->Forward();
}

void LoaderForwardAction::Stop() const
{
	_wrapper->EngageFan(false);
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

	if(_loader->IsRevCheckOn())
	{
		return Completed;
	}

	auto time = _wrapper->GetMilliseconds();

	auto duration = time - _startTime;

	if(duration > LOADER_FORWARD_TIME)
	{
		Stop();
		_errorCode = LoaderForwardTimeout;
		return Error;
	}

	if(duration > _config ->GetLoaderForwardFanTime())
	{
		_wrapper->EngageFan(false);
	}

	return Executing;
}

bool LoaderForwardAction::CheckPostConditions()
{
	return true;
}

void LoaderForwardAction::EndAction()
{
	Stop();	
}

int LoaderForwardAction::GetActionDuration()
{
	return LOADER_FORWARD_TIME;
}


