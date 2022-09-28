#include "FireCheck.h"

FireCheck::FireCheck(IArduinoWrapper* wrapper, 
	TestScreen* screen, 
	Loader* loader, 
	Actuators* actuators, 
	Sensors* sensors, 
	ButtonsController* buttons,
	Injector* injector) : IHwCheck(wrapper, screen, loader)
{
	_actuators = actuators;
	_buttons = buttons;
	_loader = loader;
	_sensors = sensors;
	_injector = injector;

	_breechOpen = false;
	_injecting = false;

	_actuators->CloseBreech();
	_actuators->TurnIgnitionOff();

	_isFwCycle = false;
	_isRevCycle = false;

	_fwCycleCounter = 0;
	_revCycleCounter = 0;

	_speedRequest = false;
}

CheckResult FireCheck::Check()
{
	if (IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}	

	_actuators->CheckHeater();

	const auto injTime = _injector->CalculateInjectionTime();

	if (IsRefreshCycle(REFRESH_CYCLE))
	{
		if (CheckCurrent(3) == Failed)
		{
			_screen->Println("Failed", 3);
			return Failed;
		}

		_screen->SetCursor(0, 0);
		_screen->Print(BLANK_LINE);
		_screen->SetCursor(0, 0);
		_screen->PrintNumber(injTime);
		_screen->Print(" ms");

		const auto press = _sensors->GetReceiverPressure();
		_screen->SetCursor(0, 1);
		_screen->Print(BLANK_LINE);
		_screen->SetCursor(0, 1);
		_screen->PrintNumber(press, 2);
		_screen->Print(" pa");		

		const auto vlt = _actuators->GetHeaterSensorVoltage();
		_screen->SetCursor(0, 3);
		_screen->Print(BLANK_LINE);
		_screen->SetCursor(0, 3);
		_screen->PrintNumber(vlt, 2);
		_screen->Print(" v");		
	}

	if (_loader->IsRevCheckOn() && _buttons->IsButtonPressed(x1A))
	{
		_wrapper->MeasuringUnitStby();
		_loader->Forward();
	}

	if (_loader->IsFwCheckOn() && _buttons->IsButtonPressed(x2B))
	{
		_wrapper->MeasuringUnitStby();
		_loader->Reverse();
	}

	if(_buttons->IsButtonPressed(x3C))
	{
		_sensors->ResetDebouncingTriggers();
		_actuators->TurnIgnitionOff();		
		_actuators->EngageInjectorDiode(false);

		if (!_injecting)
		{
			_injecting = true;
			_speedRequest = false;
			_actuators->OpenBreech();
			_actuators->CycleValveInternal();
			_actuators->TurnFanOn();

			_actuators->InjectorStart();
			_wrapper->Delay(injTime);
			_actuators->InjectorStop();	

			_wrapper->Delay(FORCED_MIXING_TIME);
			_actuators->TurnFanOff();
			_actuators->CloseBreech();
			_wrapper->Delay(BREECH_CLOSE_TIME);
			_actuators->TurnIngnitionOn();

			_wrapper->StartMeasuring();
			_actuators->EngageInjectorDiode(true);
		}
	}
	else
	{
		_injecting = false;
	}

	if (_buttons->IsButtonPressed(x5E))
	{
		ShowSpeed();
		_sensors->ResetDebouncingTriggers();
	}

	if(_buttons->IsButtonPressed(x4D))
	{
		_loader->Stop();
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
			_actuators->CycleValveExternal();
			_actuators->TurnFanOn();
		}

		if (_fwCycleCounter > 30)
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

			_actuators->TurnFanOff();
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

void FireCheck::ShowSpeed()
{
	if (!_speedRequest)
	{
		_speedRequest = true;
		
		auto speed = _wrapper->GetSpeed();
		_screen->SetCursor(8, 3);
		_screen->PrintNumber(speed, 1);
		_screen->Print("m/s");
	}
}

