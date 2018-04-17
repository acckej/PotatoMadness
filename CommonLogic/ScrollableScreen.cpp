#include "ScrollableScreen.h"
#include <stdio.h>
#include <string.h>


ScrollableScreen::ScrollableScreen(IArduinoWrapper * wrapper): ScreenBase(wrapper)
{
	_offset = 0;
	_row = 0;
	_column = 0;
	Clear();
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

	_row++;
	if(_row >= SCREEN_ROWS - 1)
	{
		_row = SCREEN_ROWS - 1;
	}
	_column = 0;

	ScreenBase::Println(message, line);
}

void ScrollableScreen::Print(char* message)
{
	auto lineBuf = GetCurrentPositionBuffer();
	sprintf(lineBuf, "%s", message);
	IncrementColumn(strlen(lineBuf));
	ScreenBase::Print(message);
}

void ScrollableScreen::PrintNumber(double number, int digits)
{
	auto lineBuf = GetCurrentPositionBuffer();
	_wrapper->PrintFormatBuffer(lineBuf, "%.*f", digits, number);	
	IncrementColumn(strlen(lineBuf));
	ScreenBase::PrintNumber(number, digits);
}

char* ScrollableScreen::GetCurrentPositionBuffer()
{
	return _screenBuffer[_row] + _column;	
}

void ScrollableScreen::PrintNumber(int number)
{
	auto lineBuf = GetCurrentPositionBuffer();
	sprintf(lineBuf, "%i", number);
	IncrementColumn(strlen(lineBuf));
	ScreenBase::PrintNumber(number);
}

void ScrollableScreen::SetCursor(char col, char row)
{
	_column = col;
	_row = row + _offset;
	ScreenBase::SetCursor(col, row);
}

void ScrollableScreen::Refresh()
{
	Clear();
	ScreenBase::Refresh();
}

void ScrollableScreen::ScrollUp()
{
	_offset--;
	if(_offset < 0)
	{
		_offset = 0;
	}
	Redraw();
}

void ScrollableScreen::ScrollDown()
{
	_offset++;
	if(_offset > SCREEN_ROWS - ACTUAL_SCREEN_ROWS)
	{
		_offset = SCREEN_ROWS - ACTUAL_SCREEN_ROWS;
	}
	Redraw();
}

void ScrollableScreen::Draw()
{
	Redraw();
}

void ScrollableScreen::Redraw()
{
	ScreenBase::Refresh();
	for (auto i = 0; i < SCREEN_ROWS; i++)
	{
		ScreenBase:SetCursor(0, i);
		ScreenBase::Print(_screenBuffer[_row]);
	}

	ScreenBase::SetCursor(_column, _row - _offset);
}

void ScrollableScreen::Clear()
{
	for (auto i = 0; i < SCREEN_ROWS; i++)
	{
		for (auto j = 0; j < SCREEN_COLUMNS; j++)
		{
			_screenBuffer[i][j] = ' ';
		}
		_screenBuffer[i][SCREEN_COLUMNS] = 0;
	}	
}

void ScrollableScreen::IncrementColumn(char length)
{
	_column += length;
	if(_column >= SCREEN_COLUMNS - 1)
	{
		_column = SCREEN_COLUMNS - 1;
	}
}
