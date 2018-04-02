#pragma once
#include "IArduinoWrapper.h"
#include "Configuration.h"

#define CONFIG_VALUES_COUNT 19

#define LOADER_FORWARD_TIME_INDEX 16
#define LOADER_REVERSE_TIME_INDEX 17
#define SSPPA_INDEX 0

struct ConfigurationValue
{
	double Value;

	double Step;

	char* Name;

	char Index;
};


class ConfigurationValueStorage : public IConfiguration
{
public:
	ConfigurationValueStorage(IArduinoWrapper * wrapper);
	~ConfigurationValueStorage();

	int GetLoaderForwardFanTime() override;
	int GetLoaderReverseFanTime() override;

	double GetSsPpA() override;
	double GetSsPpB() override;
	double GetSsPpC() override;
	double GetSsPpD() override;

	double GetMoistAirDensityA() override;
	double GetMoistAirDensityB() override;

	double GetChamberVolume() override;

	double GetValveDiameter() override;
	double GetOutflowCoefficient() override;
	double GetMolarMass() override;
	double GetNormalCondDensity() override;
	double GetNormalCondDryDensity() override;
	double GetUpMaxConcA() override;
	double GetUpMaxConcB() override;
	double GetUpMaxConcC() override;
	double GetValveBoreArea() override;
	double GetCorrectionalCoef() override;

	double GetGasFlowSpeedA() override;
	double GetGasFlowSpeedB() override;
	
	void IncrementValue(char index) override;
	void DecrementValue(char index) override;

	ConfigurationValue GetConfigurationValue(char index);
	char GetValuesCount();
	void Save() override;
	void Load();
private:
	void InitConfiguration();

	IArduinoWrapper * _wrapper;
	ConfigurationValue* _values;
	char _valuesCount;
};

