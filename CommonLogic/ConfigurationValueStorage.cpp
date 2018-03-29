#include "ConfigurationValueStorage.h"


ConfigurationValueStorage::ConfigurationValueStorage(IArduinoWrapper* wrapper)
{
	_wrapper = wrapper;
}

void ConfigurationValueStorage::IncrementValue(char index)
{
}

void ConfigurationValueStorage::DecrementValue(char index)
{
}

ConfigurationValue ConfigurationValueStorage::GetConfigurationValue(char index)
{
	return ConfigurationValue();
}

char ConfigurationValueStorage::GetValuesCount()
{
	return  _valuesCount;
}

