#pragma once
#include "ScreenBase.h"
class ManualScreen :
	public ScreenBase
{
public:
	ManualScreen(IArduinoWrapper* wrapper);	

	void DrawExtTemp(float temp);
	void DrawCurrent(float current);
	void DrawReceiverPressure(float pressure);
	void DrawAtmPressure(float pressure);

	void Draw() override;
};

