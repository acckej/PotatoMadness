#include "TestScreen.h"

TestScreen::TestScreen(IArduinoWrapper * wrapper)
{
	_wrapper = wrapper;
}

TestScreen::~TestScreen()
{
}

void TestScreen::PutTestMessage(char * message, char line) const
{
	auto ln = line - 1;
	if(ln > 3)
	{
		ln = 3;
	}
	_wrapper->SetScreenCursor(0, ln < 0 ? 0 : ln);
	_wrapper->Print(message);
}

void TestScreen::PutNumber(double number, int digits) const
{
	_wrapper->Print(number, digits);
}

void TestScreen::Refresh() const
{
	_wrapper->ClearScreen();
}
