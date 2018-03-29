#include "ConfigurationScreen.h"



ConfigurationScreen::ConfigurationScreen(IArduinoWrapper * wrapper, ConfigurationValueStorage* storage): ScrollableScreen(wrapper)
{
	_storage = storage;
	_rowIndex = 0;
	_keyPressDuration = 0;
}

void ConfigurationScreen::Draw()
{
}

void ConfigurationScreen::CursorUp()
{
}

void ConfigurationScreen::CursorDown()
{
}

void ConfigurationScreen::IncreaseValue()
{
}

void ConfigurationScreen::DecreaseValue()
{
}

void ConfigurationScreen::KeyDown()
{
}

void ConfigurationScreen::KeyUp()
{
}
