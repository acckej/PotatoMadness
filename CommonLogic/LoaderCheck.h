#pragma once
#include "IHwCheck.h"
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "Constants.h"
#include "Context.h"

class LoaderCheck : public IHwCheck
{
public:
	LoaderCheck(IArduinoWrapper* wrapper, TestScreen* screen);

	CheckResult Check() override;	
	
private:
	void Stop() const;
	CheckResult CheckCurrent(char messageLine) const;	
};

