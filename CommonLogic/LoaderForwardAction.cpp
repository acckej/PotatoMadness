#include "LoaderForwardAction.h"
#include "Constants.h"


LoaderForwardAction::LoaderForwardAction(IArduinoWrapper* wrapper, Configuration* config): IAction(wrapper)
{
	_config = config;
}

void LoaderForwardAction::Reset()
{
	IAction::Reset();	
}

bool LoaderForwardAction::CheckPreconditions()
{
	if(!_wrapper->IsFwCheckOn() || _wrapper->IsRevCheckOn())
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
	_wrapper->EngageLoader(true, true);
}

void LoaderForwardAction::Stop() const
{
	_wrapper->EngageFan(false);
	_wrapper->EngageLoader(false, false);
}

ActionState LoaderForwardAction::Execute()
{
	auto current = _wrapper->GetLoaderCurrent();

	if(current > LOADER_CURRENT_MAX)
	{
		_errorCode = LoaderOverload;
		Stop();
		return Error;
	}

	if(_wrapper->IsRevCheckOn())
	{		
		_wrapper->EngageLoader(false, true);

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


