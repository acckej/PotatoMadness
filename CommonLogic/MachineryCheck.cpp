#include "MachineryCheck.h"
#include "Context.h"

MachineryCheck::MachineryCheck(IArduinoWrapper * wrapper, TestScreen * screen, Actuators* actuators) : IHwCheck(wrapper, screen)
{
	_cyclesCounter = 0;

	_breachClose = true;
	_breachOpen = false;
	_fan = false;
	_injector = false;
	_actuators = actuators;
}

CheckResult MachineryCheck::Check()
{	
	if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
	{
		Context::Halt();
		return Interrupted;
	}

	if(_breachClose)
	{
		if(_cyclesCounter == 0)
		{
			Context::Halt();
			_screen->Refresh();
			_screen->Println("Drives check", 1);

			_actuators->CloseBreech();
		}
		_screen->Println("Breach close", 2);
		if(_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_breachClose = false;
			_actuators->DisableBreech();
			_breachOpen = true;
		}
	}

	if (_breachOpen)
	{
		if (_cyclesCounter == 0)
		{
			_actuators->OpenBreech();
		}
		_screen->Println("Breach open", 3);
		if (_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_breachOpen = false;			
			_fan = true;
		}
	}

	if (_fan)
	{
		if (_cyclesCounter == 0)
		{
			_actuators->TurnFanOn();
		}
		_screen->Println("Fan", 4);
		if (_cyclesCounter >= 30)
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
	_wrapper->Delay(100);

	return Running;
}
