#include "LoaderCheck.h"
#include "Constants.h"
#include <stdio.h>


LoaderCheck::LoaderCheck(IArduinoWrapper * wrapper, TestScreen* screen): IHwCheck(wrapper, screen)
{
	_cyclesCounter = 0;
	_forward = true;
}

CheckResult LoaderCheck::Check()
{
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
			_wrapper->EngageLoader(true, true);
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

		if(_cyclesCounter >= 50)
		{
			_forward = false;
			_wrapper->EngageLoader(false, false);
			_cyclesCounter = 0;
		}
	}
	else
	{
		if (_cyclesCounter == 0)
		{
			_screen->Println("Ldr test rev", 2);
			_wrapper->EngageLoader(false, true);
		}		

		if (Context::GetButtonsController().IsButtonPressed(TestAbortButton))
		{
			Stop();
			return Interrupted;
		}

		if (CheckCurrent(3) == Failed)
		{
			_screen->Println("Failed", 4);
			return Failed;
		}

		_cyclesCounter++;

		if (_cyclesCounter >= 50)
		{
			Stop();
			_forward = true;
			_cyclesCounter = 0;
			_screen->Println("Passed", 4);
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
	auto loaderCurrent = _wrapper->GetLoaderCurrent();
	
	if (loaderCurrent > LOADER_CURRENT_MAX)
	{
		Stop();				
		_screen->Println("Overload: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print("a");	

		return Failed;
	}

	if (loaderCurrent < LOADER_CURRENT_WORKING)
	{
		if(_wrapper->IsRevCheckOn() || _wrapper->IsFwCheckOn())
		{
			_screen->Println("Rchk:", 4);
			_screen->Print(_wrapper->IsRevCheckOn() ? "1" : "0");
			_screen->Print(";Fchk:");
			_screen->Print(_wrapper->IsFwCheckOn() ? "1" : "0");

			return Passed;
		}

		Stop();		
		_screen->Println("Low curr: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print("a");		

		return Failed;
	}

	_screen->Println("Current: ", messageLine);
	_screen->PrintNumber(loaderCurrent, 2);
	_screen->Print("a");

	return Passed;
}
