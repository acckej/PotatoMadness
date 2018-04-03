#pragma once
#include "ScrollableScreen.h"
#include "Context.h"


#define AUTOREPEAT_DELAY 2000
#define AUTOREPEAT_INTERVAL 200

class ConfigurationScreen :
	public ScrollableScreen
{
public:
	ConfigurationScreen(IArduinoWrapper * wrapper, IConfiguration* storage);
	
	void Draw() override;
private:
	void CursorUp();
	void CursorDown();
	void IncreaseValue() const;
	void DecreaseValue() const;

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

