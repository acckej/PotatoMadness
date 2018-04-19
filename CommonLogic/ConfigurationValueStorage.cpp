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
	return _values[SSPPB_INDEX].Value;
}

double ConfigurationValueStorage::GetSsPpC()
{
	return _values[SSPPC_INDEX].Value;
}

double ConfigurationValueStorage::GetSsPpD()
{
	return _values[SSPPD_INDEX].Value;
}

double ConfigurationValueStorage::GetMoistAirDensityA()
{
	return _values[MOIST_AIR_DENSITYA_INDEX].Value;
}

double ConfigurationValueStorage::GetMoistAirDensityB()
{
	return _values[MOIST_AIR_DENSITYB_INDEX].Value;
}

double ConfigurationValueStorage::GetChamberVolume()
{
	return _values[CHAMBER_VOLUME_INDEX].Value;
}

double ConfigurationValueStorage::GetValveDiameter()
{
	return _values[VALVE_DIAMETER_INDEX].Value;
}

double ConfigurationValueStorage::GetOutflowCoefficient()
{
	return _values[OUTFLOW_COEF_INDEX].Value;
}

double ConfigurationValueStorage::GetMolarMass()
{
	return _values[MOLAR_MASS_INDEX].Value;
}

double ConfigurationValueStorage::GetNormalCondDensity()
{
	return _values[NORMAL_COND_DENSITY_INDEX].Value;
}

double ConfigurationValueStorage::GetNormalCondDryDensity()
{
	return _values[NORMAL_COND_DRY_DENSITY_INDEX].Value;
}

double ConfigurationValueStorage::GetUpMaxConcA()
{
	return _values[UP_MAX_CONCA_INDEX].Value;
}

double ConfigurationValueStorage::GetUpMaxConcB()
{
	return _values[UP_MAX_CONCB_INDEX].Value;
}

double ConfigurationValueStorage::GetUpMaxConcC()
{
	return _values[UP_MAX_CONCC_INDEX].Value;
}

double ConfigurationValueStorage::GetValveBoreArea()
{
	return _values[VALVE_BORE_AREA_INDEX].Value;
}

double ConfigurationValueStorage::GetCorrectionalCoef()
{
	return _values[CORRECTIONAL_COEF_INDEX].Value;
}

double ConfigurationValueStorage::GetGasFlowSpeedA()
{
	return _values[GAS_FLOW_SPEEDA_INDEX].Value;
}

double ConfigurationValueStorage::GetGasFlowSpeedB()
{
	return _values[GAS_FLOW_SPEEDB_INDEX].Value;
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

ConfigurationValue ConfigurationValueStorage::GetConfigurationValue(char index) const
{
	return _values[index];
}

char ConfigurationValueStorage::GetValuesCount() const
{
	return  _valuesCount;
}

void ConfigurationValueStorage::Save()
{
}

void ConfigurationValueStorage::Load()
{
	InitConfiguration();
}

void ConfigurationValueStorage::InitConfiguration()
{
	_values = new ConfigurationValue[CONFIG_VALUES_COUNT];
	_valuesCount = CONFIG_VALUES_COUNT;
	_values[0] = { 0.61078f, 0.001f, "ssppA " }; // saturated steam partial pressure
	_values[1] = { 7.5f, 0.1f, "ssppB " }; 
	_values[2] = { 2048.625f, 0.01f, "ssppC " };
	_values[3] = { 35.85f, 0.01f, "ssppD " };
	_values[4] = {287.058f, 0.01f, "madA  " }; // moist air density
	_values[5] = { 461.495f, 0.01f, "madB " };
	_values[6] = { 1.5f, 0.1f, "chaV  " }; // combustion chamber volume
	_values[7] = { 6.0f, 0.1f, "valD  " }; // valve diameter
	_values[8] = { 0.4f, 0.01f, "ouCo  " }; // outflow coefficient
	_values[9] = { 58.123f, 0.01f, "moMa  " }; // molar mass
	_values[10] = { 2.51f, 0.01f, "20cDn " }; // 20c 101.325kpa density
	_values[11] = { 1.2041f, 0.001f, "20cDD " }; // 20c 101.325kpa dry air density
	_values[12] = { 44.62f, 0.01f, "UpMxA " }; // Up max concentration
	_values[13] = { 0.00367f, 0.0001f, "UpMxB " };
	_values[14] = { 32.46f, 0.01f, "UpMxC " };
	_values[15] = { 0.25f, 0.01f, "vlvBA " }; // valve bore area
	_values[16] = { 0.5f, 0.01f, "coCo  " }; // correctional coefficient
	_values[17] = { 2000.0f, 1.0f, "lFwFa " }; // loader forward fan time
	_values[18] = { 2000.0f, 1.0f, "lReFa " }; // loader reverse fan time
	_values[19] = { 91.5f, 0.1f, "gasFA " }; // gas flow speed 
	_values[20] = { 1.03f, 0.01f, "gasFB " };
}

