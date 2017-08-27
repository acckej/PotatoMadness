#include "IHwCheck.h"

IHwCheck::IHwCheck()
{
	_wrapper = nullptr;
	_screen = nullptr;
}

IHwCheck::IHwCheck(IArduinoWrapper* wrapper, TestScreen* screen)
{
	_wrapper = wrapper;
	_screen = screen;
}

CheckResult IHwCheck::Check()
{
	return CheckResult();
}
