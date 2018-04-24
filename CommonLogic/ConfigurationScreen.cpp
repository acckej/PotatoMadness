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

void ConfigurationScreen::Refresh()
{
	if(!UpdateRefreshCounter())
	{
		return;
	}

	auto count = _storage->GetValuesCount();
	for(auto i = 0; i < ACTUAL_SCREEN_ROWS; i++)
	{
		if(i + _offset >= count)
		{
			Println(BLANK_LINE, i + 1);
		}
		else
		{
			auto val = _storage->GetConfigurationValue(i + _offset);
			SetCursor(0, i);
			Print(" ");
			Print(val.Name);
			PrintNumber(val.Value, VALUE_PRECISION);
		}		
	}

	SetChar(0, _screenRow, '>');
}

/*
*		x2		x5 -- quit
*  x1		x4
*		x3		x6 -- save
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
			Refresh();
		}
		return;
	}

	if(cont.IsButtonPressed(x3C))
	{
		if (KeyDown(x3C))
		{
			CursorDown();
			Refresh();
		}
		return;
	}

	if(cont.IsButtonPressed(x6F))
	{
		if (KeyDown(x6F))
		{
			_storage->Save();
		}
		return;
	}

	if(_keyPressed)
	{
		KeyUp();
	}

	Refresh();
}

void ConfigurationScreen::CursorUp()
{
	_screenRow = _rowIndex - _offset;
	SetChar(0, _screenRow, ' ');

	_rowIndex--;

	if (_rowIndex < 0)
	{
		_rowIndex = 0;
	}

	_screenRow = _rowIndex - _offset;

	if (_screenRow < 0)
	{
		_screenRow = 0;
		ScrollUp();
	}	

	SetChar(0, _screenRow, '>');
}

void ConfigurationScreen::CursorDown()
{
	_screenRow = _rowIndex - _offset;
	SetChar(0, _screenRow, ' ');	

	_rowIndex++;

	if(_rowIndex > SCREEN_ROWS - 1)
	{
		_rowIndex = SCREEN_ROWS - 1;
	}

	_screenRow = _rowIndex - _offset;

	if(_screenRow >= ACTUAL_SCREEN_ROWS)
	{
		_screenRow = ACTUAL_SCREEN_ROWS - 1;
		ScrollDown();
	}

	SetChar(0, _screenRow, '>');
}

void ConfigurationScreen::IncreaseValue() 
{	
	_storage->IncrementValue(_rowIndex);
	UpdateCurrentValue();
}

void ConfigurationScreen::DecreaseValue()
{	
	_storage->DecrementValue(_rowIndex);
	UpdateCurrentValue();
}

void ConfigurationScreen::UpdateCurrentValue()
{
	SetCursor(VALUE_INDEX, _screenRow);
	Print(VALUE_MASK);	
	auto val = _storage->GetConfigurationValue(_rowIndex);
	SetCursor(VALUE_INDEX, _screenRow);
	PrintNumber(val.Value, VALUE_PRECISION);
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
