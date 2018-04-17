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
	void SetCursor(char col, char row) override;
	void Refresh() override;
	
	void ScrollUp();
	void ScrollDown();
	void Draw() override;
private:
	void Clear();
	void Redraw();
	char* GetCurrentPositionBuffer();
	void IncrementColumn(char length);

	char _screenBuffer[SCREEN_ROWS][SCREEN_COLUMNS + 1];	
	char _row;
	char _column;
protected:
	char _offset;
};

