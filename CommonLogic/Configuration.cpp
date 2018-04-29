#include "Configuration.h"



IConfiguration::IConfiguration()
{
}

int IConfiguration::GetLoaderForwardFanTime()
{
	return 0;
}

int IConfiguration::GetLoaderReverseFanTime()
{
	return 0;
}

double IConfiguration::GetSsPpA()
{
	return 0;
}

double IConfiguration::GetSsPpB()
{
	return 0;
}

double IConfiguration::GetSsPpC()
{
	return 0;
}

double IConfiguration::GetSsPpD()
{
	return 0;
}

double IConfiguration::GetMoistAirDensityA()
{
	return 0;
}

double IConfiguration::GetMoistAirDensityB()
{
	return 0;
}

double IConfiguration::GetChamberVolume()
{
	return 0;
}

double IConfiguration::GetValveDiameter()
{
	return 0;
}

double IConfiguration::GetOutflowCoefficient()
{
	return 0;
}

double IConfiguration::GetMolarMass()
{
	return 0;
}

double IConfiguration::GetNormalCondDensity()
{
	return 0;
}

double IConfiguration::GetNormalCondDryDensity()
{
	return 0;
}

double IConfiguration::GetUpMaxConcA()
{
	return 0;
}

double IConfiguration::GetUpMaxConcB()
{
	return 0;
}

double IConfiguration::GetUpMaxConcC()
{
	return 0;
}

double IConfiguration::GetValveBoreArea()
{
	return 0;
}

double IConfiguration::GetCorrectionalCoef()
{
	return 0;
}

int IConfiguration::GetFiringIdleCyclesCount()
{
	return 0;
}

double IConfiguration::GetGasFlowSpeedA()
{
	return 0;
}

double IConfiguration::GetGasFlowSpeedB()
{
	return 0;
}

void IConfiguration::IncrementValue(char index)
{
}

void IConfiguration::DecrementValue(char index)
{
}

void IConfiguration::Save()
{
}

ConfigurationValue IConfiguration::GetConfigurationValue(char index) const
{
	return ConfigurationValue{};
}

char IConfiguration::GetValuesCount() const
{
	return 0;
}


