#include "ScreenBase.h"

ScreenBase::ScreenBase(IArduinoWrapper * wrapper)
{
	_wrapper = wrapper;
	_refreshCounter = 0;
}

void ScreenBase::Println(const char * message, char line)
{
	auto ln = line - 1;
	if (ln > 3)
	{
		ln = 3;
	}

	auto printLine = ln < 0 ? 0 : ln;
	_wrapper->SetScreenCursor(0, printLine);
	_wrapper->Print(BLANK_LINE);
	_wrapper->SetScreenCursor(0, printLine);
	_wrapper->Print(message);
}

void ScreenBase::Print(char * message)
{
	_wrapper->Print(message);
}

void ScreenBase::PrintNumber(double number, int digits)
{
	_wrapper->Print(number, digits);
}

void ScreenBase::PrintNumber(int number)
{
	_wrapper->PrintFormat("%i", number);
}

void ScreenBase::PrintNumber(unsigned long number)
{
	_wrapper->PrintFormat("%lu", number);
}

void ScreenBase::SetCursor(char col, char row)
{
	_wrapper->SetScreenCursor(col, row);
}

void ScreenBase::Refresh()
{	
	_wrapper->ClearScreen();
}

void ScreenBase::Draw()
{
}

void ScreenBase::ResetRefreshCounter()
{
	_refreshCounter += REFRESH_DELAY;
}

bool ScreenBase::UpdateRefreshCounter()
{
	auto current = _wrapper->GetMilliseconds();

	if(current - _refreshCounter >= REFRESH_DELAY)
	{
		_refreshCounter = current;
		return true;
	}

	return false;
}
