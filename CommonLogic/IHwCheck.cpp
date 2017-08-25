#include "IHwCheck.h"

IHwCheck::IHwCheck(IArduinoWrapper* wrapper, TestScreen* screen)
{
	_wrapper = wrapper;
	_screen = screen;
}

CheckResult IHwCheck::Check()
{
	return CheckResult();
}
