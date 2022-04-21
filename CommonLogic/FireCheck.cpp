#include "FireCheck.h"

#define REFRESH_CYCLE 500

FireCheck::FireCheck(IArduinoWrapper* wrapper, 
	TestScreen* screen, 
	Loader* loader, 
	Actuators* actuators, 
	Sensors* sensors, 
	ButtonsController* buttons,
	Injector* injector) : IHwCheck(wrapper, screen)
{
	_actuators = actuators;
	_buttons = buttons;
	_loader = loader;
	_sensors = sensors;
	_injector = injector;

	_breechOpen = false;

	_actuators->CloseBreech();
	_actuators->TurnIgnitionOff();

	_isFwCycle = false;
	_isRevCycle = false;

	_fwCycleCounter = 0;
	_revCycleCounter = 0;
}

CheckResult FireCheck::Check()
{
	if (IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}

	if (CheckCurrent(2) == Failed)
	{
		_screen->Println("Failed", 3);
		return Failed;
	}

	const auto injTime = _injector->CalculateInjectionTime();

	_screen->SetCursor(0, 0);
	_screen->PrintNumber(injTime);

	if(_loader->IsRevCheckOn() && _buttons->IsButtonPressed(x1A))
	{
		_loader->Forward();
	}

	if (_loader->IsFwCheckOn() && _buttons->IsButtonPressed(x2B))
	{
		_loader->Reverse();
	}	

	if(_buttons->IsButtonPressed(x3C))
	{
		_actuators->InjectorStart();
		_wrapper->Delay(injTime);
		_actuators->InjectorStop();
	}

	if(_buttons->IsButtonPressed(x4D))
	{
		Stop();
		return Passed;
	}

	if (_loader->IsFwCheckOn())
	{
		if (!_isFwCycle)
		{
			_isFwCycle = true;
			_isRevCycle = false;
			_fwCycleCounter = 0;

			_actuators->EngageInjectorDiode(false);
			_actuators->TurnIgnitionOff();
			_actuators->OpenBreech();
			_actuators->TurnFanOn();
		}

		if (_fwCycleCounter > 40)
		{
			_fwCycleCounter = 0;
			_actuators->CloseBreech();
			_actuators->TurnFanOff();
		}
		else
		{
			_fwCycleCounter++;
		}
	}	

	if(_loader->IsRevCheckOn())
	{
		if (!_isRevCycle)
		{
			_isRevCycle = true;
			_isFwCycle = false;
			_revCycleCounter = 0;

			_actuators->CloseBreech();
		}

		if(_revCycleCounter < 20)
		{
			_revCycleCounter++;
		}
		else
		{
			_actuators->EngageInjectorDiode(true);
			_actuators->TurnIngnitionOn();
		}
	}	

	_cyclesCounter++;

	return Running;
}

void FireCheck::Stop() const
{
	_loader->Stop();
}

CheckResult FireCheck::CheckCurrent(char messageLine)
{
	const auto loaderCurrent = static_cast<double>(_loader->GetCurrent());

	if (loaderCurrent > LOADER_CURRENT_MAX)
	{
		Stop();
		_screen->Println("Overload: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print("a");

		return Failed;
	}

	if (IsRefreshCycle(REFRESH_CYCLE))
	{
		_screen->Println("Current: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print("a");
	}

	return Passed;
}
