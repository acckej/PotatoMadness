#pragma once
#include "IArduinoWrapper.h"


class ScreenBase
{
public:
	ScreenBase(IArduinoWrapper* wrapper);	

	void Println(char* message, char line) const;
	void Print(char* message) const;
	void PrintNumber(double number, int digits) const;
	void Refresh() const;

protected:
	IArduinoWrapper* _wrapper;
};

