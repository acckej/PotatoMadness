#include "ButtonsController.h"

static const char ButtonsMapData[] = { BTN1_PORT, BTN2_PORT, BTN3_PORT, BTN4_PORT, BTN5_PORT, BTN6_PORT };
const char* ButtonsController::ButtonsMap = ButtonsMapData;

ButtonsController::ButtonsController(IArduinoWrapper* wrapper, ButtonsMapItem* buttonsMap, int mapLength)
{
	_wrapper = wrapper;
	_buttonsMap = buttonsMap;
	_mapLength = mapLength;
}

bool ButtonsController::IsButtonPressed(Buttons button) const
{
	if(button == Combo)
	{
		return false;
	}

	auto result = _wrapper->DigitalRead(ButtonsMap[button]);	
	return result == ARDUINO_HIGH;
}

bool ButtonsController::AreButtonsPressed(Buttons one, Buttons two) const
{
	if (one == Combo || two == Combo)
	{
		return false;
	}

	auto resultOne = _wrapper->DigitalRead(ButtonsMap[one]);
	auto resultTwo = _wrapper->DigitalRead(ButtonsMap[two]);

	return resultOne == ARDUINO_HIGH && resultTwo == ARDUINO_HIGH;
}

void ButtonsController::RaiseButtonsEvent(OperationMode mode) const
{
	auto buttons = GetPressedButton();
	if(buttons == None || buttons == Combo)
	{
		return;
	}

	for(auto i = 0; i < _mapLength; i++)
	{
		auto item = _buttonsMap[i];

		if(item.IsMatching(buttons, mode))
		{
			item.InvokeHandler();
			return;
		}
	}
}

Buttons ButtonsController::GetPressedButton() const
{
	auto pressed = 0;
	auto button = x1A;
	if(_wrapper->DigitalRead(ButtonsMap[x1A]) == ARDUINO_HIGH)
	{
		pressed++;
	}

	if (_wrapper->DigitalRead(ButtonsMap[x2B]) == ARDUINO_HIGH)
	{
		button = x2B;
		pressed++;
	}

	if (_wrapper->DigitalRead(ButtonsMap[x3C]) == ARDUINO_HIGH)
	{
		button = x3C;
		pressed++;
	}

	if (_wrapper->DigitalRead(ButtonsMap[x4D]) == ARDUINO_HIGH)
	{
		button = x4D;
		pressed++;
	}

	if (_wrapper->DigitalRead(ButtonsMap[x5E]) == ARDUINO_HIGH)
	{
		button = x5E;
		pressed++;
	}

	if (_wrapper->DigitalRead(ButtonsMap[x6F]) == ARDUINO_HIGH)
	{
		button = x6F;
		pressed++;
	}

	if(pressed > 1)
	{
		return Combo;
	}

	if(pressed == 0)
	{
		return None;
	}

	return button;
}
