#include "MachineryCheck.h"
#include "Context.h"

MachineryCheck::MachineryCheck(IArduinoWrapper * wrapper, TestScreen * screen) : IHwCheck(wrapper, screen)
{
	_cyclesCounter = 0;

	_breachClose = true;
	_breachOpen = false;
	_fan = false;
	_injector = false;
}

CheckResult MachineryCheck::Check()
{
	if (_cyclesCounter == 0)
	{
		Context::Halt();
		_screen->Refresh();
		_screen->Println("Drives check", 1);	
	}	

	if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
	{
		Context::Halt();
		return Interrupted;
	}

	if(_breachClose)
	{
		if(_cyclesCounter == 0)
		{
			_wrapper->EngageBreach(false, true);
		}
		_screen->Println("Breach close", 2);
		if(_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_breachClose = false;
			_wrapper->EngageBreach(true, false);
			_breachOpen = true;
		}
	}

	if (_breachOpen)
	{
		if (_cyclesCounter == 0)
		{
			_wrapper->EngageBreach(true, true);
		}
		_screen->Println("Breach open", 2);
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
			_wrapper->EngageFan(true);
		}
		_screen->Println("Fan", 2);
		if (_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_fan = false;
			_wrapper->EngageFan(false);
			_wrapper->EngageBreach(false, true);
			_injector = true;
		}
	}

	if (_injector)
	{
		if (_cyclesCounter == 0)
		{
			_wrapper->EngageInjector(true);
		}
		_screen->Println("Injector", 2);
		if (_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;			
			_wrapper->EngageInjector(false);			
			_injector = false;

			return Passed;
		}
	}	

	_cyclesCounter++;
	_wrapper->Delay(100);

	return Running;
}
