#include "ScrollableScreen.h"
#include <stdio.h>


ScrollableScreen::ScrollableScreen(IArduinoWrapper * wrapper): ScreenBase(wrapper)
{
	_offset = 0;
	_row = 0;
	_column = 0;
	Clear();
}


ScrollableScreen::~ScrollableScreen()
{
}

void ScrollableScreen::Println(const char* message, char line)
{
	auto lineNum = line + _offset;
	if(lineNum > SCREEN_ROWS - ACTUAL_SCREEN_ROWS + 1)
	{
		lineNum = SCREEN_ROWS - ACTUAL_SCREEN_ROWS + 1;
	}

	if(lineNum < 0)
	{
		lineNum = 0;
	}

	auto lineBuf = _screenBuffer[lineNum];
	for(auto i = 0; i < SCREEN_COLUMNS; i++)
	{
		lineBuf[i] = ' ';
	}

	sprintf(lineBuf, "%.*s", SCREEN_COLUMNS, message);

	ScreenBase::Println(message, line);
}

void ScrollableScreen::Print(char* message)
{

}

void ScrollableScreen::PrintNumber(double number, int digits)
{
}

void ScrollableScreen::PrintNumber(int number)
{
}

void ScrollableScreen::SetCursor(char col, char row)
{
}

void ScrollableScreen::Refresh()
{
}

void ScrollableScreen::Clear()
{
	for (auto i = 0; i < SCREEN_ROWS; i++)
	{
		for (auto j = 0; j < SCREEN_COLUMNS; j++)
		{
			_screenBuffer[i][j] = ' ';
		}
	}
}
