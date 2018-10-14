#pragma once
#include "Constants.h"
#include "IArduinoWrapper.h"

#define AUTOREPEAT_DELAY 2000
#define AUTOREPEAT_INTERVAL 200

class KeyHandler
{
public:
	KeyHandler(IArduinoWrapper* wrapper);
protected:
	bool KeyDown(Buttons btn);
	void KeyUp();
	bool KeyPressed() const;
private:
	bool _keyPressed;
	long _delayStart;
	bool _autoRepeat;
	Buttons _lastButton;
	IArduinoWrapper* _wrapper;
};

