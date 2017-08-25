#pragma once
#include "IHwCheck.h"

class IArduinoWrapper;
class TestScreen;

class ButtonsCheck : IHwCheck
{
public:
	ButtonsCheck(IArduinoWrapper* wrapper, TestScreen* screen);
	~ButtonsCheck();

	CheckResult Check() override;
};

