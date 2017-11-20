#include "ScreenBase.h"

ScreenBase::ScreenBase(IArduinoWrapper * wrapper)
{
	_wrapper = wrapper;
}

void ScreenBase::Println(const char * message, char line) const
{
	auto ln = line - 1;
	if (ln > 3)
	{
		ln = 3;
	}

	auto printLine = ln < 0 ? 0 : ln;
	_wrapper->SetScreenCursor(0, printLine);
	_wrapper->Print("                    ");
	_wrapper->SetScreenCursor(0, printLine);
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

void ScreenBase::PrintNumber(int number) const
{
	_wrapper->PrintFormat("%i", number);
}

void ScreenBase::SetCursor(char col, char row) const
{
	_wrapper->SetScreenCursor(col, row);
}

void ScreenBase::Refresh() const
{
	_wrapper->ClearScreen();
}
