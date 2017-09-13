#include "LoaderReverseActionForcedMixing.h"
#include "Constants.h"


LoaderReverseActionForcedMixing::LoaderReverseActionForcedMixing(IArduinoWrapper* wrapper, Configuration* config, Injector* injector): IAction(wrapper)
{
	_config = config;
	_injector = injector;
	_injectionStart = 0;
	_isInjection = false;
	_injected = false;
	_mixed = false;
	_breachClosingStart = 0;
}

void LoaderReverseActionForcedMixing::Reset()
{
	IAction::Reset();
	_injectionStart = 0;
	_isInjection = false;
	_injected = false;
	_mixed = false;
	_breachClosingStart = 0;
}

bool LoaderReverseActionForcedMixing::CheckPreconditions()
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

	if (!_wrapper->GetAmmoSensorState())
	{
		_errorCode = NoAmmo;
		return false;
	}

	return true;
}

void LoaderReverseActionForcedMixing::StartAction()
{
	IAction::StartAction();

	_wrapper->EngageLoader(false, true);
}

bool LoaderReverseActionForcedMixing::Execute()
{
	auto time = _wrapper->GetMilliseconds();
	auto duration = time - _startTime;

	if (!_isInjection)
	{
		auto current = _wrapper->GetLoaderCurrent();
		if (current > LOADER_CURRENT_MAX)
		{
			_errorCode = LoaderOverload;
			Stop();
			return false;
		}

		if (_wrapper->IsFwCheckOn())
		{
			_wrapper->EngageLoader(false, false);
			_wrapper->EngageFan(true);

			_isInjection = true;
			_injectionStart = _wrapper->GetMilliseconds();

			return true;
		}

		if (duration > LOADER_REVERSE_TIME)
		{
			Stop();
			_errorCode = LoaderReverseTimeout;
			return false;
		}
	}
	else
	{
		if(!_injected && time - _injectionStart >= FAN_SPINUP_TIME)
		{
			auto injectionTime = _injector->CalculateInjectionTime();

			if (injectionTime <= 0 || injectionTime > MAX_INJECTION_TIME)
			{
				_errorCode = IncorrectInjectionTime;
				_wrapper->EngageFan(false);
				return false;
			}

			_wrapper->EngageInjector(true);
			_wrapper->Delay(injectionTime);
			_wrapper->EngageInjector(false);
			_wrapper->EngageIngnition(true);

			_injected = true;
			return true;
		}
		
		if(!_mixed && time - _injectionStart >= _config->GetLoaderReverseFanTime())
		{
			_mixed = true;
			_wrapper->EngageFan(false);			
			_wrapper->EngageBreach(false, true);
			_breachClosingStart = _wrapper->GetMilliseconds();

			return true;
		}

		if(_mixed && time - _breachClosingStart >= BREACH_ENGAGING_TIME)
		{
			_wrapper->EngageIngnition(true);
			_isCompleted = true;
			return false;
		}
	}

	return true;
}

bool LoaderReverseActionForcedMixing::CheckPostConditions()
{
	return false;
}

void LoaderReverseActionForcedMixing::EndAction()
{
	Stop();
}

int LoaderReverseActionForcedMixing::GetActionDuration()
{
	return 0;
}

void LoaderReverseActionForcedMixing::Stop() const
{
	_wrapper->EngageLoader(false, false);
	_wrapper->EngageIngnition(false);
	_wrapper->EngageInjector(false);
}
