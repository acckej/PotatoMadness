#include "LoaderReverseActionForcedMixing.h"
#include "Constants.h"


LoaderReverseActionForcedMixing::LoaderReverseActionForcedMixing(
	IArduinoWrapper* wrapper, Configuration* config, Injector* injector, Loader* loader, Actuators* actuators, Sensors* sensors, IAction* nextAction): IAction(wrapper, nextAction)
{
	_config = config;
	_injector = injector;
	_injectionStart = 0;
	_isInjection = false;
	_injected = false;
	_mixed = false;
	_breachClosingStart = 0;
	_loader = loader;
	_actuators = actuators;
	_sensors = sensors;
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
	if (!_loader->IsRevCheckOn())
	{
		_errorCode = IncorrectLoaderPositionRev;
		return false;
	}

	auto pressure = _sensors->GetReceiverPressure();

	if (pressure < RECEIVER_PRESSURE_MIN)
	{
		_errorCode = ReceiverPressureLow;
		return false;
	}

	if (pressure > RECEIVER_PRESSURE_MAX)
	{
		_errorCode = ReceiverPressureHigh;
		return false;
	}

	auto voltage = _sensors->GetBatteryVoltage();

	if (voltage < LOW_VOLTAGE)
	{
		_errorCode = LowVoltage;
		return false;
	}

	if (_loader->NoAmmo())
	{
		_errorCode = NoAmmo;
		return false;
	}

	return true;
}

void LoaderReverseActionForcedMixing::StartAction()
{
	IAction::StartAction();
	_loader->Reverse();
	_firingState = FrontRev;
}

ActionState LoaderReverseActionForcedMixing::Execute()
{
	auto time = _wrapper->GetMilliseconds();
	auto duration = time - _startTime;

	if (!_isInjection)
	{		
		if (_loader->IsOverload())
		{
			_errorCode = LoaderOverload;
			Stop();
			return Error;
		}

		if (_loader->IsFwCheckOn())
		{
			_loader->Stop();
			_firingState = Reversed;
			_actuators->TurnFanOn();

			_isInjection = true;
			_injectionStart = _wrapper->GetMilliseconds();

			return Executing;
		}

		if (duration > LOADER_REVERSE_TIME)
		{
			Stop();
			_errorCode = LoaderReverseTimeout;
			return Error;
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
				_actuators->TurnFanOff();
				return Error;
			}

			_actuators->InjectorStart();
			_wrapper->Delay(injectionTime);
			_actuators->InjectorStop();
			
			_injected = true;
			return Executing;
		}
		
		if(!_mixed && time - _injectionStart >= _config->GetLoaderReverseFanTime())
		{
			_mixed = true;
			_actuators->TurnFanOff();
			_actuators->CloseBreech();
			_breachClosingStart = _wrapper->GetMilliseconds();

			return Executing;
		}

		if(_mixed && time - _breachClosingStart >= BREACH_ENGAGING_TIME)
		{			
			return Completed;
		}
	}

	return Executing;
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

const char * LoaderReverseActionForcedMixing::GetActionName()
{
	return "Ldr. rev. FM";
}

void LoaderReverseActionForcedMixing::Stop() const
{
	_loader->Stop();
	_actuators->TurnFanOff();
	_actuators->CloseBreech();
	_actuators->InjectorStop();
}
