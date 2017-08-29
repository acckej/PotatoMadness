#include "ScreenBase.h"

ScreenBase::ScreenBase(IArduinoWrapper * wrapper)
{
	_wrapper = wrapper;
}

void ScreenBase::Println(char * message, char line) const
{
	auto ln = line - 1;
	if (ln > 3)
	{
		ln = 3;
	}
	_wrapper->SetScreenCursor(0, ln < 0 ? 0 : ln);
	_wrapper->Print(message);
}

void ScreenBase::Print(char * message) const
{
	_wrapper->Print(message);
}

void ScreenBase::PrintNumber(double number, int digits) const
{
	_wrapper->Print(number, digits);
}

void ScreenBase::Refresh() const
{
	_wrapper->ClearScreen();
}
