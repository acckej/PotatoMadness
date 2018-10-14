#include "KeyHandler.h"


KeyHandler::KeyHandler(IArduinoWrapper* wrapper)
{
	_keyPressed = false;
	_delayStart = 0;
	_autoRepeat = false;
	_lastButton = x5E;
	_wrapper = wrapper;
}


bool KeyHandler::KeyDown(Buttons btn)
{
	if (btn == _lastButton)
	{
		auto current = _wrapper->GetMilliseconds();
		auto delay = current - _delayStart;

		if (_autoRepeat)
		{
			if (delay > AUTOREPEAT_INTERVAL)
			{
				_delayStart = current;
				return true;
			}

			return false;
		}

		if (delay > AUTOREPEAT_DELAY)
		{
			_autoRepeat = true;
			_delayStart = current;
			return true;
		}

		return false;
	}

	if (!_keyPressed)
	{
		_delayStart = _wrapper->GetMilliseconds();
		_lastButton = btn;
		_keyPressed = true;

		return true;
	}

	KeyUp();
	return false;
}

void KeyHandler::KeyUp()
{
	_autoRepeat = false;
	_keyPressed = false;
	_delayStart = 0;
	_lastButton = x5E; //exit button
}

bool KeyHandler::KeyPressed() const
{
	return _keyPressed;
}
