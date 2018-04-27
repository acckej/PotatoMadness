#include "LoaderReverseAction.h"
#include "Constants.h"

LoaderReverseAction::LoaderReverseAction(IArduinoWrapper* wrapper, Injector* injector, Loader* loader, Actuators* actuators, Sensors* sensors, IAction* nextAction): IAction(wrapper, nextAction)
{
	_injector = injector;
	_loader = loader;
	_actuators = actuators;
	_sensors = sensors;
}

void LoaderReverseAction::Reset()
{
	IAction::Reset();
}

bool LoaderReverseAction::CheckPreconditions()
{	
	if (!_loader->IsRevCheckOn() || _loader->IsFwCheckOn())
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

	if(_loader->NoAmmo())
	{
		_errorCode = NoAmmo;
		return false;
	}

	return true;
}

void LoaderReverseAction::StartAction()
{
	IAction::StartAction();
	_loader->Reverse();
	_firingState = FrontRev;
}

ActionState LoaderReverseAction::Execute()
{
	auto time = _wrapper->GetMilliseconds();
	auto duration = time - _startTime;
	
	if (_loader->IsOverload())
	{
		_errorCode = LoaderOverload;
		Stop();
		return Error;
	}

	if (duration >= BREACH_ENGAGE_TIME)
	{
		_actuators->CloseBreech();
	}

	if (_loader->IsFwCheckOn())
	{
		_loader->Stop();
		_firingState = Reversed;
		auto injectionTime = _injector->CalculateInjectionTime();

		if(injectionTime <= 0 || injectionTime > MAX_INJECTION_TIME)
		{
			_errorCode = IncorrectInjectionTime;
			return Error;
		}
		
		_actuators->InjectorStart();
		_wrapper->Delay(injectionTime);
		_actuators->InjectorStop();

		return Completed;
	}

	if (duration > LOADER_REVERSE_TIME)
	{
		Stop();
		_errorCode = LoaderReverseTimeout;
		return Error;
	}	

	return Executing;
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

const char * LoaderReverseAction::GetActionName()
{
	return "Ldr. rev.";
}

void LoaderReverseAction::Stop() const
{	
	_loader->Stop();
	_actuators->InjectorStop();
}
