#include "MainScreen.h"
#include "Context.h"


MainScreen::MainScreen(IArduinoWrapper* wrapper): ScreenBase(wrapper)
{
}

void MainScreen::Draw()
{	
	//{ MainMenu, FiringMode, FiringModeForcedMixing, ConfigEditScreen, TestMode}
	Refresh();

	SetCursor(0, 0);
	Print("A.Fire    |");
	SetCursor(0, 1);	
	Print("C.Config  |");
	SetCursor(0, 2);
	Print("D.Test    |");

	SetCursor(13, 0);
	Print("Auto");
	SetCursor(13, 1);
	Print("Semi");	
}

void MainScreen::UpdateFiringMode()
{
	if(Context::GetFiringSequenceMode() == Auto)
	{
		SetCursor(12, 0);
		Print(">");
		SetCursor(12, 1);
		Print(" ");
	}
	else
	{
		SetCursor(12, 0);
		Print(" ");
		SetCursor(12, 1);
		Print(">");
	}
}
