#include "ConfigurationValueStorage.h"


ConfigurationValueStorage::ConfigurationValueStorage(IArduinoWrapper* wrapper)
{
	_wrapper = wrapper;
	_values = nullptr;
	_valuesCount = 0;
	Load();
}

ConfigurationValueStorage::~ConfigurationValueStorage()
{
	if (_values != nullptr)
	{
		delete _values;
	}
}

int ConfigurationValueStorage::GetLoaderForwardFanTime()
{
	return _values[LOADER_FORWARD_TIME_INDEX].Value;
}

int ConfigurationValueStorage::GetLoaderReverseFanTime()
{
	return _values[LOADER_REVERSE_TIME_INDEX].Value;
}

double ConfigurationValueStorage::GetSsPpA()
{
	return _values[SSPPA_INDEX].Value;
}

double ConfigurationValueStorage::GetSsPpB()
{
	return 0;
}

double ConfigurationValueStorage::GetSsPpC()
{
	return 0;
}

double ConfigurationValueStorage::GetSsPpD()
{
	return 0;
}

double ConfigurationValueStorage::GetMoistAirDensityA()
{
	return 0;
}

double ConfigurationValueStorage::GetMoistAirDensityB()
{
	return 0;
}

double ConfigurationValueStorage::GetChamberVolume()
{
	return 0;
}

double ConfigurationValueStorage::GetValveDiameter()
{
	return 0;
}

double ConfigurationValueStorage::GetOutflowCoefficient()
{
	return 0;
}

double ConfigurationValueStorage::GetMolarMass()
{
	return 0;
}

double ConfigurationValueStorage::GetNormalCondDensity()
{
	return 0;
}

double ConfigurationValueStorage::GetNormalCondDryDensity()
{
	return 0;
}

double ConfigurationValueStorage::GetUpMaxConcA()
{
	return 0;
}

double ConfigurationValueStorage::GetUpMaxConcB()
{
	return 0;
}

double ConfigurationValueStorage::GetUpMaxConcC()
{
	return 0;
}

double ConfigurationValueStorage::GetValveBoreArea()
{
	return 0;
}

double ConfigurationValueStorage::GetCorrectionalCoef()
{
	return 0;
}

double ConfigurationValueStorage::GetGasFlowSpeedA()
{
	return 0;
}

double ConfigurationValueStorage::GetGasFlowSpeedB()
{
	return 0;
}

void ConfigurationValueStorage::IncrementValue(char index)
{
	if(index < 0 || index >= CONFIG_VALUES_COUNT)
	{
		return;
	}

	_values[index].Value += _values[index].Step;	
}

void ConfigurationValueStorage::DecrementValue(char index)
{
	if (index < 0 || index >= CONFIG_VALUES_COUNT)
	{
		return;
	}

	_values[index].Value -= _values[index].Step;
}

ConfigurationValue ConfigurationValueStorage::GetConfigurationValue(char index)
{
	return _values[index];
}

char ConfigurationValueStorage::GetValuesCount()
{
	return  _valuesCount;
}

void ConfigurationValueStorage::Save()
{
}

void ConfigurationValueStorage::Load()
{
}

void ConfigurationValueStorage::InitConfiguration()
{
	_values = new ConfigurationValue[CONFIG_VALUES_COUNT];
	_valuesCount = CONFIG_VALUES_COUNT;
	_values[0] = { 0.61078f, 0.001f, "ssppA", 1 }; // saturated steam partial pressure
	_values[1] = { 7.5f, 0.1f, "ssppB", 2}; 
	_values[2] = { 2048.625f, 0.01f, "ssppC", 3 };
	_values[3] = { 35.85f, 0.01f, "ssppD", 4 };
	_values[4] = {287.058f, 0.01f, "mo ai de A", 5}; // moist air density
	_values[5] = { 461.495f, 0.01f, "mo ai de B", 6 };
	_values[6] = { 1.5f, 0.1f, "chamber vol", 7 }; // combustion chamber volume
	_values[7] = { 6.0f, 0.1f, "valve diam", 8 }; // valve diameter
	_values[8] = { 0.4f, 0.01f, "outflow coef", 9 }; // outflow coefficient
	_values[9] = { 58.123f, 0.01f, "molar mass", 10 }; // molar mass
	_values[10] = { 2.51f, 0.01f, "20c 101kpa dens", 11 }; // 20c 101.325kpa density
	_values[11] = { 1.2041f, 0.001f, "20c 101kpa Ddens", 12 }; // 20c 101.325kpa dry air density
	_values[12] = { 44.62f, 0.01f, "Up max concA", 13 }; // Up max concentration
	_values[13] = { 0.00367f, 0.0001f, "Up max concB", 14 };
	_values[14] = { 32.46f, 0.01f, "Up max concC", 15 };
	_values[15] = { 0.25f, 0.01f, "valve bore area", 16 }; // valve bore area
	_values[16] = { 0.5f, 0.01f, "corr coef", 17 }; // correctional coefficient
	_values[17] = { 2000.0f, 1.0f, "ldr fw fan", 18 }; // loader forward fan time
	_values[18] = { 2000.0f, 1.0f, "ldr rev fan", 19 }; // loader reverse fan time
	_values[19] = { 91.5f, 0.1f, "gas flow A", 20 }; // gas flow speed 
	_values[20] = { 1.03f, 0.01f, "gas flow B", 21 };
}

