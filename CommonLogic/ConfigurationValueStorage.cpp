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
	return static_cast<int>(_values[LOADER_FORWARD_TIME_INDEX].Value);
}

int ConfigurationValueStorage::GetLoaderReverseFanTime()
{
	return static_cast<int>(_values[LOADER_REVERSE_TIME_INDEX].Value);
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

int ConfigurationValueStorage::GetFiringIdleCyclesCount()
{
	return static_cast<int>(_values[FIRING_IDLE_CYCLES_INDEX].Value);
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

	if(_values[index].Value < 0)
	{
		_values[index].Value = 0;
	}
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
	if(_values == nullptr)
	{
		return;
	}

	for (auto i = 0; i < CONFIG_VALUES_COUNT; i++)
	{
		SaveDoubleToEeprom(_values[i].Value, i * sizeof(double));
	}

	_wrapper->WriteToEeprom(CONFIG_VALUES_COUNT * sizeof(double) + 1, CONFIG_UPDATED_FLAG);
}

void ConfigurationValueStorage::Load()
{
	InitConfiguration();
	if(_wrapper->ReadFromEeprom(CONFIG_VALUES_COUNT * sizeof(double) + 1) == CONFIG_UPDATED_FLAG)
	{
		for (auto i = 0; i < CONFIG_VALUES_COUNT; i++)
		{
			auto val = GetDoubleFromEeeprom(i * sizeof(double));
			_values[i].Value = val;
		}
	}
}

void ConfigurationValueStorage::InitConfiguration()
{
	_values = new ConfigurationValue[CONFIG_VALUES_COUNT];
	_valuesCount = CONFIG_VALUES_COUNT;
	_values[SSPPA_INDEX] = { 0.61078l, 0.001l, "ssppA " }; // saturated steam partial pressure
	_values[SSPPB_INDEX] = { 7.5l, 0.1l, "ssppB " };
	_values[SSPPC_INDEX] = { 2048.625l, 0.01l, "ssppC " };
	_values[SSPPD_INDEX] = { 35.85l, 0.01l, "ssppD " };
	_values[MOIST_AIR_DENSITYA_INDEX] = {287.058l, 0.01l, "madA  " }; // moist air density
	_values[MOIST_AIR_DENSITYB_INDEX] = { 461.495l, 0.01l, "madB " };
	_values[CHAMBER_VOLUME_INDEX] = { 7.0l, 0.1l, "chaV  " }; // combustion chamber volume
	_values[VALVE_DIAMETER_INDEX] = { 4.0l, 0.1l, "valD  " }; // valve diameter (6.0l)
	_values[OUTFLOW_COEF_INDEX] = { 0.4l, 0.01l, "ouCo  " }; // outflow coefficient
	_values[MOLAR_MASS_INDEX] = { 58.123l, 0.01l, "moMa  " }; // molar mass
	_values[NORMAL_COND_DENSITY_INDEX] = { 2.51l, 0.01l, "20cDn " }; // 20c 101.325kpa density
	_values[NORMAL_COND_DRY_DENSITY_INDEX] = { 1.2041l, 0.001l, "20cDD " }; // 20c 101.325kpa dry air density
	_values[UP_MAX_CONCA_INDEX] = { 44.62l, 0.01l, "UpMxA " }; // Up max concentration
	_values[UP_MAX_CONCB_INDEX] = { 0.00367l, 0.0001l, "UpMxB " };
	_values[UP_MAX_CONCC_INDEX] = { 32.46l, 0.01l, "UpMxC " };
	_values[VALVE_BORE_AREA_INDEX] = { 0.006l, 0.001l, "vlvBA " }; // valve bore area (0.25l)
	_values[CORRECTIONAL_COEF_INDEX] = { 1.5l, 0.01l, "coCo  " }; // correctional coefficient
	_values[LOADER_FORWARD_TIME_INDEX] = { 2000.0l, 1.0l, "lFwFa " }; // loader forward fan time
	_values[LOADER_REVERSE_TIME_INDEX] = { 2000.0l, 1.0l, "lReFa " }; // loader reverse fan time
	_values[GAS_FLOW_SPEEDA_INDEX] = { 91.5l, 0.1l, "gasFA " }; // gas flow speed 
	_values[GAS_FLOW_SPEEDB_INDEX] = { 1.03l, 0.01l, "gasFB " };
	_values[FIRING_IDLE_CYCLES_INDEX] = { 10.0l, 1.0l, "ficc  " }; // firing idle cycles count
}

ArduinoDouble ConfigurationValueStorage::GetDoubleFromEeeprom(short address) const
{
	unsigned char temp[4];

	temp[0] = _wrapper->ReadFromEeprom(address);
	temp[1] = _wrapper->ReadFromEeprom(static_cast<short>(address + 1));
	temp[2] = _wrapper->ReadFromEeprom(static_cast<short>(address + 2));
	temp[3] = _wrapper->ReadFromEeprom(static_cast<short>(address + 3));

	const auto result = *reinterpret_cast<ArduinoDouble*>(temp);
	return result;
}

void ConfigurationValueStorage::SaveDoubleToEeprom(ArduinoDouble val, short address) const
{
	const auto value = reinterpret_cast<unsigned char*>(&val);

	_wrapper->WriteToEeprom(address, value[0]);
	_wrapper->WriteToEeprom(static_cast<short>(address + 1), value[1]);
	_wrapper->WriteToEeprom(static_cast<short>(address + 2), value[2]);
	_wrapper->WriteToEeprom(static_cast<short>(address + 3), value[3]);
}

