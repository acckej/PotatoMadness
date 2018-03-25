#pragma once
#include "ScreenBase.h"

#define SCREEN_ROWS 10
#define SCREEN_COLUMNS 20

class ScrollableScreen : public ScreenBase
{
public:
	ScrollableScreen(IArduinoWrapper * wrapper);
	
	void Println(const char* message, char line) override;
	void Print(char* message) override;
	void PrintNumber(double number, int digits) override;
	void PrintNumber(int number) override;
	void SetCursor(char col, char row) override;
	void Refresh() override;
	
	void ScrollUp();
	void ScrollDown();
private:
	void Clear();
	void Redraw();
	char* GetCurrentPositionBuffer();

	char _screenBuffer[SCREEN_ROWS][SCREEN_COLUMNS];
	char _offset;
	char _row;
	char _column;
};
