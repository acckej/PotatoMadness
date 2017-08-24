#include "LoaderCheck.h"
#include <stdio.h>

LoaderCheck::LoaderCheck(IArduinoWrapper * wrapper, ITestScreen* screen)
{
	_wrapper = wrapper;
	_screen = screen;
}

CheckResult LoaderCheck::Check()
{
	Context::Halt();
	_screen->Refresh();
	_screen->PutTestMessage("Loader check, test forward", 1);

	_wrapper->DigitalWrite(LOADER_FWD_PORT, 1);
	_wrapper->DigitalWrite(LOADER_REV_PORT, 1);
	_wrapper->DigitalWrite(LOADER_ENABLE_PORT, 1);
	
	for (auto i = 0; i < 50; i++)
	{
		if(Context::GetButtonsController().IsButtonPressed(TestAbortButton))
		{
			Stop();
			
			return Interrupted;
		}

		if(CheckCurrent(2) == Failed)
		{
			return Failed;
		}
	}

	_screen->PutTestMessage("Loader check, test reverse", 3);

	for (auto i = 0; i < 50; i++)
	{
		if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
		{
			Stop();
			return Interrupted;
		}

		if (CheckCurrent(4) == Failed)
		{
			return Failed;
		}
	}

	return Passed;
}

void LoaderCheck::Stop() const
{
	_wrapper->DigitalWrite(LOADER_ENABLE_PORT, 0);
	_wrapper->DigitalWrite(LOADER_FWD_PORT, 0);
	_wrapper->DigitalWrite(LOADER_REV_PORT, 0);
}

CheckResult LoaderCheck::CheckCurrent(char messageLine) const
{
	auto loaderCurrent = _wrapper->AnalogRead(LOADER_CURRENT_PORT);
	char buf[SCREEN_BUFFER_SIZE];
	if (loaderCurrent > LOADER_CURRENT_MAX)
	{
		Stop();		
		sprintf(buf, "Overload %i", loaderCurrent);
		_screen->PutTestMessage(buf, messageLine);

		return Failed;
	}

	if (loaderCurrent < LOADER_CURRENT_WORKING)
	{
		Stop();		
		sprintf(buf, "Low curr %i", loaderCurrent);
		_screen->PutTestMessage(buf, messageLine);

		return Failed;
	}

	sprintf(buf, "Current %i", loaderCurrent);
	_screen->PutTestMessage(buf, messageLine);

	return Passed;
}
