#include "Injector.h"



Injector::Injector(Configuration* config, IArduinoWrapper* wrapper)
{
	_configuration = config;
	_wrapper = wrapper;
}

unsigned long Injector::CalculateInjectionTime()
{
	return 0;
}



