#pragma once
struct ConfigurationValue
{
	double Value;

	double Step;

	char* Name;	
};

class IConfiguration
{
public:
	virtual ~IConfiguration() = default;
	IConfiguration();

	virtual int GetLoaderForwardFanTime();
	virtual int GetLoaderReverseFanTime();

	virtual double GetSsPpA();
	virtual double GetSsPpB();
	virtual double GetSsPpC();
	virtual double GetSsPpD();

	virtual double GetMoistAirDensityA();
	virtual double GetMoistAirDensityB();

	virtual double GetChamberVolume();

	virtual double GetValveDiameter();
	virtual double GetOutflowCoefficient();
	virtual double GetMolarMass();
	virtual double GetNormalCondDensity();
	virtual double GetNormalCondDryDensity();
	virtual double GetUpMaxConcA();
	virtual double GetUpMaxConcB();
	virtual double GetUpMaxConcC();
	virtual double GetValveBoreArea();
	virtual double GetCorrectionalCoef();

	virtual double GetGasFlowSpeedA();
	virtual double GetGasFlowSpeedB();

	virtual void IncrementValue(char index);
	virtual void DecrementValue(char index);

	virtual void Save();

	virtual ConfigurationValue GetConfigurationValue(char index) const;
	virtual char GetValuesCount() const;
};

