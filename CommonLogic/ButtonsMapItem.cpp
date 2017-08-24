#include "ButtonsMapItem.h"



ButtonsMapItem::ButtonsMapItem(Buttons button, OperationMode mode, ButtonPressedEventDelegate handler)
{
	_button = button;
	_mode = mode;
	_delegate = handler;
}

bool ButtonsMapItem::IsMatching(Buttons button, OperationMode mode)
{
	return _button == button && mode == _mode;
}

void ButtonsMapItem::InvokeHandler()
{
	if(_delegate != nullptr)
	{
		_delegate();
	}
}
