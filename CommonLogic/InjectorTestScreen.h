#pragma once
#include "ScreenBase.h"
#include "Sensors.h"
#include "Injector.h"

class InjectorTestScreen :
	public ScreenBase
{
public:
	InjectorTestScreen(IArduinoWrapper* wrapper, Sensors* sensors, Injector* injector);	

	void Draw() override;
private:
	Sensors * _sensors;
	Injector* _injector;
};

