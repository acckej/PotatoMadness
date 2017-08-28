#pragma once
#include "IArduinoWrapper.h"
#include "TestScreen.h"

enum CheckResult {Passed, Interrupted, Failed, Running};

class IHwCheck
{
public:
	IHwCheck();
	IHwCheck(IArduinoWrapper* wrapper, TestScreen* screen);
	virtual CheckResult Check();

protected:
	IArduinoWrapper* _wrapper;
	TestScreen* _screen;
};

