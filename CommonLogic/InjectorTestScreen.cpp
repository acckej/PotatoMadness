#include "InjectorTestScreen.h"

InjectorTestScreen::InjectorTestScreen(IArduinoWrapper* wrapper, Sensors* sensors, Injector* injector): ScreenBase(wrapper)
{
	_injector = injector;
	_sensors = sensors;
}

void InjectorTestScreen::Draw()
{
	SetCursor(0, 0);
	Print("Out. tmp:");
	PrintNumber(_wrapper->GetExternalTemp(), 1);

	SetCursor(0, 1);
	Print("Atm. prsr:");
	PrintNumber(_wrapper->GetAtmPressure(), 1);

	SetCursor(0, 2);
	Print("Humid:");
	PrintNumber(_wrapper->GetExternalHumidity(), 1);

	SetCursor(0, 3);
	Print("Rcv. prsr:");
	PrintNumber(_sensors->GetReceiverPressure(), 1);

	SetCursor(14, 0);	
	Print(">");
	PrintNumber(_injector->CalculateInjectionTime());
}
