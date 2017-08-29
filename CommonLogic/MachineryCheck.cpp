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
			_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_HIGH);
		}
		_screen->Println("Breach close", 2);
		if(_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_breachClose = false;
			_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_LOW);
			_breachOpen = true;
		}
	}

	if (_breachOpen)
	{
		if (_cyclesCounter == 0)
		{
			_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_HIGH);
		}
		_screen->Println("Breach open", 2);
		if (_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_breachOpen = false;
			_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_LOW);
			_fan = true;
		}
	}

	if (_fan)
	{
		if (_cyclesCounter == 0)
		{
			_wrapper->DigitalWrite(FAN_PORT, ARDUINO_HIGH);
		}
		_screen->Println("Fan", 2);
		if (_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;
			_fan = false;
			_wrapper->DigitalWrite(FAN_PORT, ARDUINO_LOW);
			_injector = true;
		}
	}

	if (_injector)
	{
		if (_cyclesCounter == 0)
		{
			_wrapper->DigitalWrite(INJECTOR_PORT, ARDUINO_HIGH);
		}
		_screen->Println("Injector", 2);
		if (_cyclesCounter >= 30)
		{
			_cyclesCounter = 0;			
			_wrapper->DigitalWrite(INJECTOR_PORT, ARDUINO_LOW);
			_injector = false;

			return Passed;
		}
	}	

	_cyclesCounter++;
	_wrapper->Delay(100);

	return Running;
}
