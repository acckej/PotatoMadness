#include "Context.h"

OperationMode Context::_mode;
IArduinoWrapper* Context::_wrapper;
ButtonsController* Context::_buttonsController;
Loader* Context::_loader;
Actuators* Context::_actuators;
SystemState Context::_state;

Context::Context(IArduinoWrapper *wrapper, ButtonsController* buttons, Loader* loader, Actuators* actuators)
{
	_mode = FiringMode;
	_wrapper = wrapper;
	_buttonsController = buttons;
	_loader = loader;
	_actuators = actuators;
	_state = SystemIdle;
}


OperationMode Context::GetOperationMode()
{
	return _mode;
}

void Context::SetOperationMode(OperationMode mode)
{
	_mode = mode;
}

void Context::Halt()
{
	_loader->Stop();
	_actuators->TurnFanOff();
	_actuators->InjectorStop();
	_actuators->CloseBreech();	
	_actuators->IgnitionOff();
	_actuators->AuxOff();
	_actuators->EngageInjectorDiode(false);	
}

void Context::HandleError(char * message, ErrorCodes code)
{
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

