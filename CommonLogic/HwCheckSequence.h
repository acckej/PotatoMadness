#pragma once
#include "IHwCheck.h"
#include "IArduinoWrapper.h"

class HwCheckSequence
{
public:
	HwCheckSequence(IArduinoWrapper* wrapper, IHwCheck* checks, int checksCount);
	~HwCheckSequence();

	CheckResult Run() const;
private:
	IHwCheck* _checks;
	IArduinoWrapper* _wrapper;
	int _checksCount;
};

