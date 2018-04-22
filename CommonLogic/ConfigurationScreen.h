#pragma once
#include "ScrollableScreen.h"
#include "Context.h"


#define AUTOREPEAT_DELAY 200
#define AUTOREPEAT_INTERVAL 2000
#define VALUE_INDEX 8
#define VALUE_MASK "             "
#define NAME_LENGTH 6
#define VALUE_PRECISION 5


class ConfigurationScreen :
	public ScrollableScreen
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

	bool KeyDown(Buttons btn);
	void KeyUp();

	IConfiguration* _storage;
	char _rowIndex;	
	char _screenRow;
	bool _keyPressed;
	long _delayStart;
	bool _autoRepeat;
	Buttons _lastButton;
};

