#pragma once
#include "Constants.h"

typedef void(*ButtonPressedEventDelegate)();

class ButtonsMapItem
{
public:
	ButtonsMapItem(Buttons button, OperationMode mode, ButtonPressedEventDelegate handler);

	bool IsMatching(Buttons button, OperationMode mode);
	void InvokeHandler();
private:
	Buttons _button;
	OperationMode _mode;
	ButtonPressedEventDelegate _delegate;
};

