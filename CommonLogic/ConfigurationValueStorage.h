#pragma once
#include "IArduinoWrapper.h"

struct ConfigurationValue
{
	double Value;

	double Step;

	char* Name;

	char Index;
};

class ConfigurationValueStorage
{
public:
	ConfigurationValueStorage(IArduinoWrapper * wrapper);
	
	void IncrementValue(char index);
	void DecrementValue(char index);

	ConfigurationValue GetConfigurationValue(char index);
	char GetValuesCount();
private:
	IArduinoWrapper * _wrapper;
	ConfigurationValue* _values;
	char _valuesCount;
};

