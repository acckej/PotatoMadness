#pragma once
#include "Constants.h"
#include "IArduinoWrapper.h"
#include "IButtonsController.h"

class Context 
{
public:
	Context(IArduinoWrapper *wrapper, IButtonsController* buttons);

	static OperationMode GetOperationMode();
	static void SetOperationMode(OperationMode mode);

	static void Halt();

	static void HandleError(char* message, ErrorCode code);

	static bool WaitForButton(Buttons button, int delay);	

	static IButtonsController GetButtonsController();
private:
	static OperationMode _mode;
	static IArduinoWrapper* _wrapper;
	static IButtonsController* _buttonsController;
};

