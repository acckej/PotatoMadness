#pragma once
#include "HwCheckBase.h"

class HwCheckSequence
{
public:
	HwCheckSequence();
	~HwCheckSequence();
private:
	HwCheckBase* _checks;
};

