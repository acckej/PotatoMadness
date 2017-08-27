#pragma once
#include "IHwCheck.h"

class IArduinoWrapper;
class TestScreen;

class ButtonsCheck : public IHwCheck
{
public:
	ButtonsCheck(IArduinoWrapper* wrapper, TestScreen* screen);	

	CheckResult Check() override;
};

