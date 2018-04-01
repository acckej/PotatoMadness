#pragma once
#include "ScrollableScreen.h"
#include "Context.h"
#include "ConfigurationValueStorage.h"

#define AUTOREPEAT_DELAY 2000
#define AUTOREPEAT_INTERVAL 200

class ConfigurationScreen :
	public ScrollableScreen
{
public:
	ConfigurationScreen(IArduinoWrapper * wrapper, ConfigurationValueStorage* storage);
	
	void Draw() override;
private:
	void CursorUp();
	void CursorDown();
	void IncreaseValue();
	void DecreaseValue();

	bool KeyDown(Buttons btn);
	void KeyUp();

	ConfigurationValueStorage* _storage;
	char _rowIndex;	
	char _screenRow;
	bool _keyPressed;
	long _delayStart;
	bool _autoRepeat;
	Buttons _lastButton;
};

