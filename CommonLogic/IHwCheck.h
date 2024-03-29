#pragma once
#include "Loader.h"
#include "TestScreen.h"

enum CheckResult {Passed, Interrupted, Failed, Running};

#define CYCLE_DURATION 100

class IHwCheck
{
public:
	virtual ~IHwCheck() = default;
	IHwCheck();
	IHwCheck(IArduinoWrapper* wrapper, TestScreen* screen, Loader* loader);
	virtual CheckResult Check();

protected:
	IArduinoWrapper* _wrapper;
	TestScreen* _screen;
	Loader* _loader;
	int _cyclesCounter;
	long _lastCycle;
	long _refreshCycle;

	bool IsIdleCycle(int duration);
	bool IsRefreshCycle(int duration);
	CheckResult CheckCurrent(char messageLine) const;
};

