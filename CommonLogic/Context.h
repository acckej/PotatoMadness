#pragma once
#include "Constants.h"
#include "IArduinoWrapper.h"
#include "ButtonsController.h"
#include "loader.h"

class Context 
{
public:
	Context(IArduinoWrapper *wrapper, ButtonsController* buttons, Loader* loader);

	static OperationMode GetOperationMode();
	static void SetOperationMode(OperationMode mode);

	static void Halt();

	static void HandleError(char* message, ErrorCodes code);

	static bool WaitForButton(Buttons button, int delay);	

	static ButtonsController GetButtonsController();

	static void LogMessage(char* message);	
private:
	static OperationMode _mode;
	static IArduinoWrapper* _wrapper;
	static ButtonsController* _buttonsController;
	static Loader* _loader;
};

