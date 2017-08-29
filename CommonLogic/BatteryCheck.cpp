#include "BatteryCheck.h"
#include "Context.h"

BatteryCheck::BatteryCheck(IArduinoWrapper * wrapper, TestScreen * screen) : IHwCheck(wrapper, screen)
{
	_cyclesCounter = 0;
}

CheckResult BatteryCheck::Check()
{
	if (_cyclesCounter == 0)
	{
		Context::Halt();
		_screen->Refresh();
		_screen->Println("Power check", 1);
	}
	
	auto vlt = _wrapper->AnalogRead(VOLTAGE_PORT);
	auto calculated = static_cast<double>(vlt) * ANALOG_COEFFICIENT * VOLTAGE_COEFFICIENT;

	_screen->Println("Voltage:", 2);
	_screen->PrintNumber(calculated, 2);

	if(calculated <= LOW_VOLTAGE)
	{
		_screen->Println("Low voltage", 3);
		return Failed;
	}
	
	_cyclesCounter++;

	if(_cyclesCounter >= 50)
	{
		_cyclesCounter = 0;
		return Passed;
	}

	_wrapper->Delay(100);

	return Running;
}
