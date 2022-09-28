#include "IHwCheck.h"
#include "Constants.h"

IHwCheck::IHwCheck()
{
	_wrapper = nullptr;
	_screen = nullptr;
	_cyclesCounter = 0;
	_lastCycle = 0;
	_refreshCycle = 0;
}

IHwCheck::IHwCheck(IArduinoWrapper* wrapper, TestScreen* screen, Loader* loader)
{
	_wrapper = wrapper;
	_screen = screen;
	_cyclesCounter = 0;
	_lastCycle = 0;
	_refreshCycle = 0;
	_loader = loader;
}

CheckResult IHwCheck::Check()
{
	return CheckResult();
}

bool IHwCheck::IsIdleCycle(int duration)
{
	auto current = _wrapper->GetMilliseconds();

	if(current - _lastCycle > duration)
	{
		_lastCycle = current;
		return false;
	}

	return true;
}

bool IHwCheck::IsRefreshCycle(int duration)
{
	auto current = _wrapper->GetMilliseconds();

	if (current - _refreshCycle > duration)
	{
		_refreshCycle = current;
		return true;
	}

	return false;
}

CheckResult IHwCheck::CheckCurrent(char messageLine) const
{
	const auto loaderCurrent = static_cast<double>(_loader->GetCurrent());

	if (loaderCurrent > LOADER_CURRENT_MAX)
	{
		_loader->Stop();
		_screen->Println("Overload: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print(" a");

		return Failed;
	}

	_screen->Println("Current: ", messageLine);
	_screen->PrintNumber(loaderCurrent, 2);
	_screen->Print(" a");

	return Passed;
}


