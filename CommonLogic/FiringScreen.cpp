#include "FiringScreen.h"



FiringScreen::FiringScreen(IArduinoWrapper * wrapper) : ScreenBase(wrapper)
{
}

void FiringScreen::PrintStatus(char row, const char * message) const
{
	if(row > 1)
	{
		row = 1;
	}

	if(row < 0)
	{
		row = 0;
	}

	Println(message, row);
}

void FiringScreen::PrintVoltage(float voltage) const
{
	SetCursor(0, 2);
	Print("     ");
	SetCursor(0, 2);
	PrintNumber(voltage, 1);
	Print("v");
	SetCursor(0, 0);
}

void FiringScreen::PrintTemperature(float temperature) const
{
	SetCursor(6, 2);
	Print("   ");
	SetCursor(6, 2);
	PrintNumber(temperature, 1);
	Print("c");
	SetCursor(0, 0);
}

void FiringScreen::PrintLoaderCurrent(float current) const
{
	SetCursor(11, 2);
	Print("Ldr:     ");
	SetCursor(11, 2);
	PrintNumber(current, 1);
	Print("a");
	SetCursor(0, 0);
}

void FiringScreen::PrintSpeed(float speed) const
{
	SetCursor(7, 3);
	Print("      ");
	SetCursor(7, 3);
	PrintNumber(speed, 1);
	Print("m/s");
	SetCursor(0, 0);
}

void FiringScreen::PrintHumidity(float humidity) const
{
	SetCursor(16, 3);
	Print("     ");
	SetCursor(16, 3);
	PrintNumber(humidity, 1);
	Print("%rh");
	SetCursor(0, 0);
}

void FiringScreen::PrintPressure(float pressure) const
{
	SetCursor(0, 3);
	Print("      ");
	SetCursor(0, 3);
	PrintNumber(pressure, 1);
	Print("atm");
	SetCursor(0, 0);
}
