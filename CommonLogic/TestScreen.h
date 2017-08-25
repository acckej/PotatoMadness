#pragma once
#include "IArduinoWrapper.h"

class TestScreen
{
public:
	TestScreen(IArduinoWrapper* wrapper);
	~TestScreen();

	void PutTestMessage(char* message, char line) const;

	void PutNumber(double number, int digits) const;

	void Refresh() const;

private:
	IArduinoWrapper* _wrapper;
};

