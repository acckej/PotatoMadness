#include "Context.h"

OperationMode Context::_mode;
IArduinoWrapper* Context::_wrapper;
ButtonsController* Context::_buttonsController;

Context::Context(IArduinoWrapper *wrapper, ButtonsController* buttons)
{
	_mode = FiringMode;
	_wrapper = wrapper;
	_buttonsController = buttons;
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
	_wrapper->DigitalWrite(LOADER_ENABLE_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(LOADER_FWD_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(LOADER_REV_PORT, ARDUINO_LOW);

	_wrapper->DigitalWrite(INJECTOR_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_HIGH);
	_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(FAN_PORT, ARDUINO_LOW);

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
#ifdef Debug
	_wrapper->SerialPrint(message);
#endif
}
