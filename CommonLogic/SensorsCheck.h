#pragma once
#include "IHwCheck.h"

class SensorsCheck : public IHwCheck
{
public:
	SensorsCheck(IArduinoWrapper* wrapper, TestScreen* screen);

	CheckResult Check() override;
private:
	bool _shotSensors;
	bool _extEnv;
	bool _intEnv;
	bool _receiver;
	bool _ammoSensor;
};

