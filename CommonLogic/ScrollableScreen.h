#pragma once
#include "ScreenBase.h"

#define SCREEN_ROWS 30
#define SCREEN_COLUMNS 20

class ScrollableScreen : public ScreenBase
{
public:
	ScrollableScreen(IArduinoWrapper * wrapper);
	
	void Println(const char* message, char line) override;
	void Print(char* message) override;
	void PrintNumber(double number, int digits) override;
	void PrintNumber(int number) override;	
	void Refresh() override;
	void SetCursor(char col, char row) override;
	
	void ScrollUp();
	void ScrollDown();
	
	void SetChar(char col, char row, char chr);
private:	
	void Redraw();
	char* GetCurrentPositionBuffer();
	void RestoreCursor();
	void IncrementColumn(char length);

	char _screenBuffer[SCREEN_ROWS][SCREEN_COLUMNS + 1];	
	char _row;
	char _column;
protected:
	void Clear();
	char _offset;
};

