#include "LoaderReverseAction.h"
#include "Constants.h"

LoaderReverseAction::LoaderReverseAction(IArduinoWrapper* wrapper, Injector* injector): IAction(wrapper)
{
	_injector = injector;
}

void LoaderReverseAction::Reset()
{
	IAction::Reset();
}

bool LoaderReverseAction::CheckPreconditions()
{
	if (!_wrapper->IsRevCheckOn())
	{
		_errorCode = IncorrectLoaderPositionRev;
		return false;
	}

	auto voltage = _wrapper->GetBatteryVoltage();

	if (voltage < LOW_VOLTAGE)
	{
		_errorCode = LowVoltage;
		return false;
	}

	if(!_wrapper->GetAmmoSensorState())
	{
		_errorCode = NoAmmo;
		return false;
	}

	return true;
}

void LoaderReverseAction::StartAction()
{
	IAction::StartAction();

	_wrapper->EngageLoader(false, true);
}

bool LoaderReverseAction::Execute()
{
	auto time = _wrapper->GetMilliseconds();
	auto duration = time - _startTime;

	auto current = _wrapper->GetLoaderCurrent();
	if (current > LOADER_CURRENT_MAX)
	{
		_errorCode = LoaderOverload;
		Stop();
		return false;
	}

	if (duration >= BREACH_ENGAGE_TIME)
	{
		_wrapper->EngageBreach(false, true);
	}

	if (_wrapper->IsFwCheckOn())
	{
		_wrapper->EngageLoader(false, false);
		auto injectionTime = _injector->CalculateInjectionTime();

		if(injectionTime <= 0 || injectionTime > MAX_INJECTION_TIME)
		{
			_errorCode = IncorrectInjectionTime;
			return false;
		}
		
		_wrapper->EngageInjector(true);
		_wrapper->Delay(injectionTime);
		_wrapper->EngageInjector(false);
		_wrapper->EngageIngnition(true);
		_isCompleted = true;

		return false;
	}

	if (duration > LOADER_REVERSE_TIME)
	{
		Stop();
		_errorCode = LoaderReverseTimeout;
		return false;
	}	

	return true;
}

bool LoaderReverseAction::CheckPostConditions()
{
	return true;
}

void LoaderReverseAction::EndAction()
{
	Stop();
}

int LoaderReverseAction::GetActionDuration()
{
	return 0;
}

void LoaderReverseAction::Stop() const
{	
	_wrapper->EngageLoader(false, false);
	_wrapper->EngageIngnition(false);
	_wrapper->EngageInjector(false);
}
