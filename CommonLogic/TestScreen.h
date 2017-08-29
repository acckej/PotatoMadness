#pragma once
#include "IArduinoWrapper.h"
#include "ScreenBase.h"

class TestScreen : public ScreenBase
{
public:
	TestScreen(IArduinoWrapper* wrapper);
};

