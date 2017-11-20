#pragma once
#include "Constants.h"
#include "IArduinoWrapper.h"
#include "ButtonsController.h"
#include "loader.h"
#include "Actuators.h"

class Context 
{
public:
	Context(IArduinoWrapper *wrapper, ButtonsController* buttons, Loader* loader, Actuators* actuators);

	static OperationMode GetOperationMode();
	static void SetOperationMode(OperationMode mode);

	static void Halt();

	static void HandleError(char* message, ErrorCodes code);

	static bool WaitForButton(Buttons button, int delay);	

	static ButtonsController GetButtonsController();

	static void LogMessage(char* message);
	
	static SystemState GetState();

	static void SetState(SystemState state);

private:
	static OperationMode _mode;
	static SystemState _state;
	static IArduinoWrapper* _wrapper;
	static ButtonsController* _buttonsController;
	static Loader* _loader;
	static Actuators* _actuators;
};

