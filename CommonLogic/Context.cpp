#include "Context.h"

OperationMode Context::_mode;
FiringSequenceMode Context::_firingSequenceMode;
IArduinoWrapper* Context::_wrapper;
ButtonsController* Context::_buttonsController;
Loader* Context::_loader;
Actuators* Context::_actuators;
Sensors* Context::_sensors;
SystemState Context::_state;
IConfiguration* Context::_configuration;
ErrorCodes Context::_errorCode;
int Context::_idleCyclesCount;
int Context::_idleCyclesCounter;
bool Context::_backToMainScreen;

//volatile unsigned long Context::_fMicros;
//volatile unsigned long Context::_rMicros;
//volatile int Context::_order;
//volatile int Context::_digit;

Context::Context(IArduinoWrapper *wrapper, ButtonsController* buttons, Loader* loader, Actuators* actuators, Sensors* sensors, IConfiguration* configuration)
{
	_mode = MainMenu;
	_wrapper = wrapper;
	_buttonsController = buttons;
	_loader = loader;
	_actuators = actuators;
	_state = SystemRunning;
	_sensors = sensors;
	_configuration = configuration;
	_idleCyclesCount = _configuration->GetFiringIdleCyclesCount();
	_idleCyclesCounter = 0;
	_backToMainScreen = false;
}


OperationMode Context::GetOperationMode()
{
	return _mode;
}

void Context::SetOperationMode(OperationMode mode)
{
	if(mode == MainMenu)
	{
		_backToMainScreen = false;
	}

	_mode = mode;
}

void Context::Halt()
{
	_loader->Stop();
	_actuators->TurnFanOff();
	_actuators->InjectorStop();
	_actuators->CloseBreech();	
	_actuators->TurnIgnitionOff();
	_actuators->HeaterOff();
	_actuators->EngageInjectorDiode(false);	
	_sensors->ResetDebouncingTriggers();
	_idleCyclesCounter = 0;
	_actuators->TurnMixingFanOff();
}

void Context::HandleError(char * message, ErrorCodes code)
{
	_idleCyclesCounter = 0;
}

bool Context::WaitForButton(Buttons button, int delay)
{
	for(auto i = 0; i < delay / 100; i++)
	{
		if(_buttonsController->IsButtonPressed(button))
		{
			return true;
		}

		_wrapper->Delay(100);
	}

	return false;
}

ButtonsController Context::GetButtonsController()
{
	return *_buttonsController;
}

Loader* Context::GetLoader()
{
	return _loader;
}

Actuators* Context::GetActuators()
{
	return _actuators;
}

Sensors* Context::GetSensors()
{
	return _sensors;
}

IConfiguration* Context::GetConfiguration()
{
	return _configuration;
}

void Context::LogMessage(char * message)
{
#ifdef Debug
	_wrapper->SerialPrint(message);
#endif
}

SystemState Context::GetState()
{
	return _state;
}

void Context::SetState(SystemState state)
{
	_state = state;

	if(state == IdleCycle)
	{
		_idleCyclesCounter = 0;
	}
}

void Context::SetFiringSequenceMode(FiringSequenceMode mode)
{
	_firingSequenceMode = mode;
}

FiringSequenceMode Context::GetFiringSequenceMode()
{
	return _firingSequenceMode;
}

void Context::SetErrorCode(ErrorCodes code)
{
	_errorCode = code;
}

ErrorCodes Context::GetErrorCode()
{
	return _errorCode;
}

void Context::BackToMainScreen()
{
	_backToMainScreen = true;
}

bool Context::IsMainScreenRequested()
{
	return _backToMainScreen;
}

bool Context::IncrementIdleCycleCounter()
{
	_idleCyclesCounter++;
	return _idleCyclesCounter < _idleCyclesCount;
}

