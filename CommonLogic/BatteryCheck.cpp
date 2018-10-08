#include "BatteryCheck.h"
#include "Context.h"

#define BATTERY_CHECK_UPDATE_RATE 500

BatteryCheck::BatteryCheck(IArduinoWrapper * wrapper, TestScreen * screen, Sensors* sensors) : IHwCheck(wrapper, screen)
{
	_cyclesCounter = 0;
	_sensors = sensors;
}

CheckResult BatteryCheck::Check()
{
	if (_cyclesCounter == 0)
	{
		Context::Halt();
		_screen->Refresh();
		_screen->Println("Power check", 1);
	}	

	if(IsIdleCycle(BATTERY_CHECK_UPDATE_RATE))
	{
		return Running;
	}
	
	auto calculated = _sensors->GetBatteryVoltage();
		
	_screen->Println("Voltage:", 2);
	_screen->PrintNumber(calculated, 2);

	if(calculated <= LOW_VOLTAGE)
	{
		_screen->Println("Low voltage", 3);
		return Failed;
	}
	
	_cyclesCounter++;

	if(_cyclesCounter >= 100)
	{
		_cyclesCounter = 0;
		return Passed;
	}

	//_wrapper->Delay(100);

	return Running;
}
