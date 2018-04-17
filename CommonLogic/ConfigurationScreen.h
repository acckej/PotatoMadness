#pragma once
#include "ScrollableScreen.h"
#include "Context.h"


#define AUTOREPEAT_DELAY 2000
#define AUTOREPEAT_INTERVAL 200
#define VALUE_INDEX 13
#define VALUE_MASK "       "
#define NAME_LENGTH 12
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

