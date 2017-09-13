#pragma once
#include "Configuration.h"
#include "IArduinoWrapper.h"

class Injector
{
public:
	Injector(Configuration* config, IArduinoWrapper* wrapper);

	unsigned long CalculateInjectionTime();
private:
	Configuration* _configuration;
	IArduinoWrapper* _wrapper;
};

