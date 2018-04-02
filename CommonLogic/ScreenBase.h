#pragma once
#include "IArduinoWrapper.h"

#define BLANK_LINE "                    "
#define ACTUAL_SCREEN_ROWS 4

class ScreenBase
{
public:
	virtual ~ScreenBase() = default;
	ScreenBase(IArduinoWrapper* wrapper);	

	virtual void Println(const char* message, char line);
	virtual void Print(char* message);
	virtual void PrintNumber(double number, int digits);
	virtual void PrintNumber(int number);
	virtual void SetCursor(char col, char row);
	virtual void Refresh();
	virtual void Draw();

protected:
	IArduinoWrapper* _wrapper;
};

