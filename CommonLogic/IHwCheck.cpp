#include "IHwCheck.h"

IHwCheck::IHwCheck()
{
	_wrapper = nullptr;
	_screen = nullptr;
	_cyclesCounter = 0;
	_lastCycle = 0;
}

IHwCheck::IHwCheck(IArduinoWrapper* wrapper, TestScreen* screen)
{
	_wrapper = wrapper;
	_screen = screen;
	_cyclesCounter = 0;
	_lastCycle = 0;
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
