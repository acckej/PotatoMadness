#pragma once
#include "Constants.h"
#include "IArduinoWrapper.h"
#include "ButtonsMapItem.h"

class ButtonsController 
{
public:
	ButtonsController(IArduinoWrapper* wrapper, ButtonsMapItem* buttonsMap, int mapLength);

	bool IsButtonPressed(Buttons button) const;

	bool AreButtonsPressed(Buttons one, Buttons two) const;

	void RaiseButtonsEvent(OperationMode mode) const;	

	Buttons GetPressedButton() const;
private:
	IArduinoWrapper* _wrapper;
	static const char* ButtonsMap;
	ButtonsMapItem* _buttonsMap;
	int _mapLength;
};

