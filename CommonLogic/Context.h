#pragma once
#include "Constants.h"
#include "IArduinoWrapper.h"
#include "ButtonsController.h"
#include "loader.h"
#include "Actuators.h"
#include "Sensors.h"
#include "Configuration.h"

class Context 
{
public:
	Context(IArduinoWrapper *wrapper, ButtonsController* buttons, Loader* loader, Actuators* actuators, Sensors* sensors, IConfiguration* configuration);

	static OperationMode GetOperationMode();
	static void SetOperationMode(OperationMode mode);

	static void Halt();

	static void HandleError(char* message, ErrorCodes code);

	static bool WaitForButton(Buttons button, int delay);	

	static ButtonsController GetButtonsController();
		
	static Loader* GetLoader();
	static Actuators* GetActuators();
	static Sensors* GetSensors();
	
	static IConfiguration* GetConfiguration();

	static void LogMessage(char* message);
	
	static SystemState GetState();
	static void SetState(SystemState state);

	static void SetFiringSequenceMode(FiringSequenceMode mode);
	static FiringSequenceMode GetFiringSequenceMode();

	static void SetErrorCode(ErrorCodes code);
	static ErrorCodes GetErrorCode();

	static void BackToMainScreen();
	static bool IsMainScreenRequested();

	static bool IncrementIdleCycleCounter();
private:
	static OperationMode _mode;
	static SystemState _state;
	static IArduinoWrapper* _wrapper;
	static ButtonsController* _buttonsController;
	static Loader* _loader;
	static Actuators* _actuators;
	static FiringSequenceMode _firingSequenceMode;
	static Sensors* _sensors;
	static IConfiguration* _configuration;
	static ErrorCodes _errorCode;
	static int _idleCyclesCount;
	static int _idleCyclesCounter;
	static bool _backToMainScreen;
};

