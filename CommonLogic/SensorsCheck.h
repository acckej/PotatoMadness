#pragma once
#include "IHwCheck.h"
#include "Loader.h"
#include "Actuators.h"
#include "Sensors.h"

class SensorsCheck : public IHwCheck
{
public:
	SensorsCheck(IArduinoWrapper* wrapper, TestScreen* screen, Loader* loader, Actuators* actuators, Sensors* sensors);

	CheckResult Check() override;
private:
	bool _shotSensors;
	bool _extEnv;
	bool _intEnv;
	bool _receiver;
	bool _ammoSensor;
	Loader* _loader;
	Actuators* _actuators;
	Sensors* _sensors;
};

