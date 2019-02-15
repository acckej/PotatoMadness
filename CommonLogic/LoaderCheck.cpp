#include "LoaderCheck.h"
#include "Constants.h"
#include <stdio.h>

#define REFRESH_CYCLE 500

LoaderCheck::LoaderCheck(IArduinoWrapper * wrapper, TestScreen* screen, Loader* loader): IHwCheck(wrapper, screen)
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

		if(_cyclesCounter >= 100)
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

		if (_cyclesCounter >= 100)
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

CheckResult LoaderCheck::CheckCurrent(char messageLine) 
{
	auto loaderCurrent = _loader->GetCurrent();
	
	if (loaderCurrent > LOADER_CURRENT_MAX)
	{
		Stop();				
		_screen->Println("Overload: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print("a");	

		return Failed;
	}

	//if (loaderCurrent < LOADER_CURRENT_WORKING)
	//{
	//	if(_loader->IsRevCheckOn() || _loader->IsFwCheckOn())
	//	{
	//		_screen->Println("Rchk:", 4);
	//		_screen->Print(_loader->IsRevCheckOn() ? "1" : "0");
	//		_screen->Print(";Fchk:");
	//		_screen->Print(_loader->IsFwCheckOn() ? "1" : "0");

	//		return Passed;
	//	}

	//	/*Stop();		
	//	_screen->Println("Low curr: ", messageLine);
	//	_screen->PrintNumber(loaderCurrent, 2);
	//	_screen->Print("a");		

	//	return Failed;*/
	//}

	if (IsRefreshCycle(REFRESH_CYCLE))
	{
		_screen->Println("Current: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print("a");
		_screen->Println(_loader->IsFwCheckOn() ? "fc1 rc" : "fc0 rc", 3);
		_screen->Print(_loader->IsRevCheckOn() ? "1" : "0");
	}

	return Passed;
}
