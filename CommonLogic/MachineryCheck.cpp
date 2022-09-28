#include "MachineryCheck.h"
#include "Context.h"

MachineryCheck::MachineryCheck(IArduinoWrapper * wrapper, TestScreen * screen, Actuators* actuators) : IHwCheck(wrapper, screen, nullptr)
{
	_cyclesCounter = 0;

	_breechClose = true;
	_breechOpen = false;
	_fan = false;
	_injector = false;
	_actuators = actuators;
	_cycleInternal = false;
}

CheckResult MachineryCheck::Check()
{	
	if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
	{
		Context::Halt();
		return Interrupted;
	}

	if(IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}

	if(_breechClose)
	{
		if(_cyclesCounter == 0)
		{
			Context::Halt();
			_screen->Refresh();
			_screen->Println("Drives check", 1);

			_actuators->CloseBreech();
			_actuators->CycleValveExternal();
		}

		if (IsRefreshCycle(REFRESH_CYCLE))
		{
			_screen->Println("Breech close", 2);
		}
		if(_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_breechClose = false;
			_actuators->DisableBreech();
			_breechOpen = true;
		}
	}

	if (_breechOpen)
	{
		if (_cyclesCounter == 0)
		{
			_actuators->OpenBreech();			
		}
		if (IsRefreshCycle(REFRESH_CYCLE))
		{
			_screen->Println("Breech open", 3);
		}
		if (_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_breechOpen = false;			
			_fan = true;
		}
	}

	if (_fan)
	{
		if (_cyclesCounter == 0)
		{
			_actuators->TurnFanOn();
		}
		if (IsRefreshCycle(REFRESH_CYCLE))
		{
			_screen->Println("Fan", 4);
		}
		if (_cyclesCounter >= 20 && !_cycleInternal)
		{
			_actuators->CycleValveInternal();
			_cycleInternal = true;
		}

		if (_cyclesCounter >= 40)
		{
			_cyclesCounter = 0;
			_fan = false;
			_actuators->TurnFanOff();
			_actuators->CloseBreech();
			_injector = true;
		}
	}

	if (_injector)
	{
		if (_cyclesCounter == 0)
		{
			_screen->Print(" Injector");
			_actuators->InjectorStart();
		}
		
		if (_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;			
			_actuators->InjectorStop();
			_screen->Print(" Injector-> Ok");
			_injector = false;

			return Passed;
		}
	}	

	_cyclesCounter++;
	
	return Running;
}
