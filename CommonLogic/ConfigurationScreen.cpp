#include "ConfigurationScreen.h"

ConfigurationScreen::ConfigurationScreen(IArduinoWrapper * wrapper, IConfiguration* storage): ScrollableScreen(wrapper), KeyHandler(wrapper)
{
	_storage = storage;
	_rowIndex = 0;	
	_screenRow = 0;	
}

void ConfigurationScreen::Refresh()
{
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

	if (cont.IsButtonPressed(x5E))
	{
		Context::BackToMainScreen();
		return;
	}

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

	if(KeyPressed())
	{
		KeyUp();
	}	
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

