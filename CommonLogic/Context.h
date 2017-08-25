#pragma once
#include "Constants.h"
#include "IArduinoWrapper.h"
#include "ButtonsController.h"

class Context 
{
public:
	Context(IArduinoWrapper *wrapper, ButtonsController* buttons);

	static OperationMode GetOperationMode();
	static void SetOperationMode(OperationMode mode);

	static void Halt();

	static void HandleError(char* message, ErrorCode code);

	static bool WaitForButton(Buttons button, int delay);	

	static ButtonsController GetButtonsController();

	static void LogMessage(char* message);
private:
	static OperationMode _mode;
	static IArduinoWrapper* _wrapper;
	static ButtonsController* _buttonsController;
};

