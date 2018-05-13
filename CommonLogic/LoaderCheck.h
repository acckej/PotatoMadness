#pragma once
#include "IHwCheck.h"
#include "IArduinoWrapper.h"
#include "TestScreen.h"
#include "Context.h"

class LoaderCheck : public IHwCheck
{
public:
	LoaderCheck(IArduinoWrapper* wrapper, TestScreen* screen, Loader* loader);

	CheckResult Check() override;	
	
private:
	void Stop() const;
	CheckResult CheckCurrent(char messageLine);	
	
	bool _forward;
	Loader* _loader;
};

