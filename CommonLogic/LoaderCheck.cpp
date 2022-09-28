#include "LoaderCheck.h"
#include "Constants.h"
#include <stdio.h>

LoaderCheck::LoaderCheck(IArduinoWrapper * wrapper, TestScreen* screen, Loader* loader): IHwCheck(wrapper, screen, loader)
{
	_cyclesCounter = 0;
	_forward = true;
	_loader = loader;
}

CheckResult LoaderCheck::Check()
{
	if(IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}

#ifdef Debug
	char buf[100];
	sprintf(buf, "Loader fwd:%i, cycle %i", _forward, _cyclesCounter);
	Context::LogMessage(buf);
#endif

	if (_forward)
	{
		if (_cyclesCounter == 0)
		{
			Context::Halt();
			_screen->Refresh();
			
			_screen->Println("Ldr test fwd", 1);			
			_loader->Forward();
			_wrapper->Delay(200);
		}		

		if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
		{
			Stop();
			_screen->Println("Interrupted", 4);
			return Interrupted;
		}

		if (CheckCurrent(2) == Failed)
		{
			_screen->Println("Failed", 4);
			return Failed;
		}
		
		_cyclesCounter++;

		if(_cyclesCounter >= 30)
		{
			_forward = false;
			_loader->Stop();
			_cyclesCounter = 0;
		}
	}
	else
	{
		if (_cyclesCounter == 0)
		{
			_screen->Println("Ldr test rev", 2);
			_loader->Reverse();
		}		

		if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
		{
			Stop();
			return Interrupted;
		}

		if (CheckCurrent(4) == Failed)
		{
			_screen->Println("Failed", 4);
			return Failed;
		}

		_cyclesCounter++;

		if (_cyclesCounter >= 30)
		{
			Stop();
			_forward = true;
			_cyclesCounter = 0;
			_screen->Println("Passed", 4);
			return Passed;
		}
	}

	//_wrapper->Delay(100);

	return Running;
}

void LoaderCheck::Stop() const
{
	_loader->Stop();
}