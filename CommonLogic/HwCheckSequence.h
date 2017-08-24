#pragma once
#include "IHwCheck.h"

class HwCheckSequence
{
public:
	HwCheckSequence();
	~HwCheckSequence();
private:
	IHwCheck* _checks;
};

