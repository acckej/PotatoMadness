#include "ConfigurationScreen.h"



ConfigurationScreen::ConfigurationScreen(IArduinoWrapper * wrapper, IConfiguration* storage): ScrollableScreen(wrapper)
{
	_storage = storage;
	_rowIndex = 0;
	_keyPressed = false;
	_delayStart = 0;
	_autoRepeat = false;
	_lastButton = x5E;
	_screenRow = 0;
}

/*
*		x2		x5
*  x1		x4
*		x3		x6
*/

void ConfigurationScreen::Draw()
{
	auto cont = Context::GetButtonsController();

	if(cont.IsButtonPressed(x1A))
	{
		if (KeyDown(x1A))
		{
			DecreaseValue();
		}
		return;
	}

	if(cont.IsButtonPressed(x4D))
	{
		if (KeyDown(x4D))
		{
			IncreaseValue();
		}	
		return;
	}

	if(cont.IsButtonPressed(x2B))
	{
		if (KeyDown(x2B))
		{
			CursorUp();
		}
		return;
	}

	if(cont.IsButtonPressed(x3C))
	{
		if (KeyDown(x3C))
		{
			CursorDown();
		}
		return;
	}

	if(cont.IsButtonPressed(x6F))
	{
		_storage->Save();
		return;
	}

	if(_keyPressed)
	{
		KeyUp();
	}
}

void ConfigurationScreen::CursorUp()
{
	_screenRow = _rowIndex - _offset;
	SetCursor(0, _screenRow);
	Print(" ");

	_rowIndex--;

	if (_rowIndex < 0)
	{
		_rowIndex = 0;
	}

	_screenRow = _rowIndex - _offset;

	if (_screenRow < 0)
	{
		_screenRow = 0;
	}

	ScrollDown();

	SetCursor(0, _screenRow);
	Print(">");
}

void ConfigurationScreen::CursorDown()
{
	_screenRow = _rowIndex - _offset;
	SetCursor(0, _screenRow);
	Print(" ");

	_rowIndex++;

	if(_rowIndex > SCREEN_ROWS - 1)
	{
		_rowIndex = SCREEN_ROWS - 1;
	}

	_screenRow = _rowIndex - _offset;

	if(_screenRow >= SCREEN_ROWS)
	{
		_screenRow = SCREEN_ROWS - 1;
	}
	
	ScrollUp();

	SetCursor(0, _screenRow);
	Print(">");
}

void ConfigurationScreen::IncreaseValue() const
{
	_storage->IncrementValue(_rowIndex);
}

void ConfigurationScreen::DecreaseValue() const
{
	_storage->DecrementValue(_rowIndex);
}

bool ConfigurationScreen::KeyDown(Buttons btn)
{
	if(btn == _lastButton)
	{	
		auto current = _wrapper->GetMilliseconds();
		auto delay = current - _delayStart;

		if(_autoRepeat)
		{
			if(delay > AUTOREPEAT_INTERVAL)
			{
				_delayStart = current;
				return true;
			}

			return false;
		}		
		
		if(delay > AUTOREPEAT_DELAY)
		{
			_autoRepeat = true;
			_delayStart = current;
			return true;
		}

		return false;
	}

	if(!_keyPressed)
	{
		_delayStart = _wrapper->GetMilliseconds();
		_lastButton = btn;
		_keyPressed = true;

		return true;
	}

	KeyUp();
	return false;
}

void ConfigurationScreen::KeyUp()
{	
	_autoRepeat = false;
	_keyPressed = false;
	_delayStart = 0;
	_lastButton = x5E; //exit button
}