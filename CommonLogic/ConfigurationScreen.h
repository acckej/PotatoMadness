#pragma once
#include "ScrollableScreen.h"
class ConfigurationValueStorage;

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

	void KeyDown();
	void KeyUp();

	ConfigurationValueStorage* _storage;
	char _rowIndex;
	int _keyPressDuration;
	bool _keyPressed;
};

