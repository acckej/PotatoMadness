#pragma once
#include "IArduinoWrapper.h"
#include "Configuration.h"
#include "TypeDefinitions.h"

#define SSPPA_INDEX 0
#define SSPPB_INDEX 1
#define SSPPC_INDEX 2
#define SSPPD_INDEX 3
#define MOIST_AIR_DENSITYA_INDEX 4
#define MOIST_AIR_DENSITYB_INDEX 5
#define CHAMBER_VOLUME_INDEX 6
#define VALVE_DIAMETER_INDEX 7
#define OUTFLOW_COEF_INDEX 8
#define MOLAR_MASS_INDEX 9
#define NORMAL_COND_DENSITY_INDEX 10
#define NORMAL_COND_DRY_DENSITY_INDEX 11
#define UP_MAX_CONCA_INDEX 12
#define UP_MAX_CONCB_INDEX 13
#define UP_MAX_CONCC_INDEX 14
#define VALVE_BORE_AREA_INDEX 15
#define CORRECTIONAL_COEF_INDEX 16
#define LOADER_FORWARD_TIME_INDEX 17
#define LOADER_REVERSE_TIME_INDEX 18
#define GAS_FLOW_SPEEDA_INDEX 19
#define GAS_FLOW_SPEEDB_INDEX 20
#define FIRING_IDLE_CYCLES_INDEX 21

#define CONFIG_VALUES_COUNT 22
#define CONFIG_UPDATED_FLAG 99


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

	int GetFiringIdleCyclesCount() override;
	
	void IncrementValue(char index) override;
	void DecrementValue(char index) override;

	ConfigurationValue GetConfigurationValue(char index) const override;
	char GetValuesCount() const override;
	void Save() override;
	void Load();
private:
	void InitConfiguration();

	ArduinoDouble GetDoubleFromEeeprom(short address) const;
	void SaveDoubleToEeprom(ArduinoDouble val, short address) const;


	IArduinoWrapper * _wrapper;
	ConfigurationValue* _values;
	char _valuesCount;
};

