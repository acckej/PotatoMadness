#include "LoaderCheck.h"
#include <stdio.h>
#include "Constants.h"


LoaderCheck::LoaderCheck(IArduinoWrapper * wrapper, TestScreen* screen): IHwCheck(wrapper, screen)
{
	_cyclesCounter = 0;
	_forward = true;
}

CheckResult LoaderCheck::Check()
{
	if (_cyclesCounter == 0)
	{
		Context::Halt();
		_screen->Refresh();		
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
			_screen->Println("Loader check, test forward", 1);
			_wrapper->EngageLoader(true, true);
		}		

		if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
		{
			Stop();
			return Interrupted;
		}

		if (CheckCurrent(2) == Failed)
		{
			return Failed;
		}
		
		_cyclesCounter++;

		if(_cyclesCounter >= 50)
		{
			_forward = false;
			_cyclesCounter = 0;
		}
	}
	else
	{
		if (_cyclesCounter == 0)
		{
			_screen->Println("Loader check, test reverse", 3);
			_wrapper->EngageLoader(false, true);
		}		

		if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
		{
			Stop();
			return Interrupted;
		}

		if (CheckCurrent(4) == Failed)
		{
			return Failed;
		}

		_cyclesCounter++;

		if (_cyclesCounter >= 50)
		{
			Stop();
			_forward = true;
			_cyclesCounter = 0;
			return Passed;
		}
	}

	_wrapper->Delay(100);

	return Running;
}

void LoaderCheck::Stop() const
{
	_wrapper->EngageLoader(false, false);
}

CheckResult LoaderCheck::CheckCurrent(char messageLine) const
{
	auto loaderCurrent = _wrapper->AnalogRead(LOADER_CURRENT_PORT);
	char buf[SCREEN_BUFFER_SIZE];
	if (loaderCurrent > LOADER_CURRENT_MAX)
	{
		Stop();		
		sprintf(buf, "Overload %i", loaderCurrent);
		_screen->Println(buf, messageLine);

		return Failed;
	}

	if (loaderCurrent < LOADER_CURRENT_WORKING)
	{
		Stop();		
		sprintf(buf, "Low curr %i", loaderCurrent);
		_screen->Println(buf, messageLine);

		return Failed;
	}

	sprintf(buf, "Current %i", loaderCurrent);
	_screen->Println(buf, messageLine);

	return Passed;
}
