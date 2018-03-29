#pragma once
#include "ScreenBase.h"
class MainScreen :
	public ScreenBase
{
public:
	MainScreen(IArduinoWrapper* wrapper);	

	void Draw() override;

	void UpdateFiringMode();
};

