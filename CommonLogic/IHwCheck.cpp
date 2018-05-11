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

bool IHwCheck::IsIdleCycle(int duration) const
{
	auto current = _wrapper->GetMilliseconds();
	return current - _lastCycle <= duration;
}
