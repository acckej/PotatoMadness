#pragma once
#include "Constants.h"

class IButtonsController 
{
public:
	virtual bool IsButtonPressed(Buttons button);

	virtual void RaiseButtonsEvent(OperationMode mode);	
};

