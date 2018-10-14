#pragma once
#include "ScrollableScreen.h"
#include "Context.h"
#include "KeyHandler.h"

#define VALUE_INDEX 7
#define VALUE_MASK "             "
#define NAME_LENGTH 6
#define VALUE_PRECISION 5


class ConfigurationScreen :
	public ScrollableScreen,
	public KeyHandler
{
public:
	ConfigurationScreen(IArduinoWrapper * wrapper, IConfiguration* storage);
	void Refresh() override;

	void Draw() override;
private:
	void CursorUp();
	void CursorDown();
	void IncreaseValue();
	void DecreaseValue();		
	void UpdateCurrentValue();	

	IConfiguration* _storage;
	char _rowIndex;	
	char _screenRow;	
};

