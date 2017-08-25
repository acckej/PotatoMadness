#include "Context.h"

Context::Context(IArduinoWrapper *wrapper, ButtonsController* buttons)
{
	_mode = FiringMode;
	_wrapper = wrapper;
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
	_wrapper->DigitalWrite(LOADER_ENABLE_PORT, 0);
	_wrapper->DigitalWrite(LOADER_FWD_PORT, 0);
	_wrapper->DigitalWrite(LOADER_REV_PORT, 0);	
}

void Context::HandleError(char * message, ErrorCode code)
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
	_wrapper->SerialPrint(message);
}
