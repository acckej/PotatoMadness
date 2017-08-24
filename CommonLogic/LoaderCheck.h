#pragma once
#include "IHwCheck.h"
#include "IArduinoWrapper.h"
#include "ITestScreen.h"
#include "Constants.h"
#include "Context.h"

class LoaderCheck : IHwCheck
{
public:
	LoaderCheck(IArduinoWrapper* wrapper, ITestScreen* screen);

	CheckResult Check() override;	
	
private:
	IArduinoWrapper* _wrapper;
	ITestScreen* _screen;

	void Stop() const;
	CheckResult CheckCurrent(char messageLine) const;	
};

