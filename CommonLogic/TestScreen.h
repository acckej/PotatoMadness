#pragma once
#include "IArduinoWrapper.h"
#include "ScreenBase.h"

#define REFRESH_CYCLE 500

class TestScreen : public ScreenBase
{
public:
	TestScreen(IArduinoWrapper* wrapper);
};

