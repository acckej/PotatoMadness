#include "IgnitionCheck.h"
#include "Constants.h"

IgnitionCheck::IgnitionCheck(IArduinoWrapper* wrapper, TestScreen* screen, Loader* loader, Actuators* actuators) : IHwCheck(wrapper, screen)
{
	_cyclesCounter = 0;	
	_loader = loader;
	_actuators = actuators;
	_isFwd = false;
}

CheckResult IgnitionCheck::Check()
{
	if (IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}

	if (_cyclesCounter == 0)
	{
		Context::Halt();
		_screen->Refresh();

		_screen->Println("Ign test: lfwd", 1);
		_loader->Forward();
		_wrapper->Delay(200);
	}

	if (CheckCurrent(2) == Failed)
	{
		_screen->Println("Failed", 4);
		return Failed;
	}

	if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
	{
		Stop();
		_screen->Println("Interrupted", 4);
		return Interrupted;
	}

	if (_loader->IsFwCheckOn())
	{
		_screen->Refresh();
		_screen->Println("Ign test: ON", 1);
		_actuators->TurnIngnitionOn();		
		_isFwd = true;
	}

	if(_cyclesCounter > 50 && !_isFwd)
	{
		_screen->Println("Failed, ldr time", 3);
		return Failed;
	}

	if(_cyclesCounter > 500)
	{
		Stop();
		_cyclesCounter = 0;
		_actuators->TurnIgnitionOff();
		_screen->Println("Completed", 4);
		return Passed;
	}

	_cyclesCounter++;

	return Running;
}

void IgnitionCheck::Stop() const
{
	_loader->Stop();
}

CheckResult IgnitionCheck::CheckCurrent(char messageLine)
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

