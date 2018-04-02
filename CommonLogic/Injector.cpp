#include "Injector.h"
#include <math.h>
#include "CalculationConstants.h"

#define M_PI 3.1415926535897932384626433832795

Injector::Injector(IConfiguration* config, IArduinoWrapper* wrapper, Sensors* sensors)
{
	_configuration = config;
	_wrapper = wrapper;
	_sensors = sensors;
}

unsigned long Injector::CalculateInjectionTime() const
{
	auto time = KILO * GetInjectedPortion() * GetGasFlow();	
	return time;
}

double Injector::GetSaturatedSteamPartialPressure() const
{
	//=0.61078*10^(((7.5*(F2+273.15))-2048.625)/((F2+273.15)-35.85))
	auto externalTemp = _wrapper->GetExternalTemp();
	auto result = pow(_configuration->GetSsPpA() * 10, (_configuration->GetSsPpB() * (externalTemp + KELVIN) - _configuration->GetSsPpC()) / (externalTemp + KELVIN - _configuration->GetSsPpD()));

	return result;
}

double Injector::GetSteamPressure() const
{
	auto result = _wrapper->GetExternalHumidity() * GetSaturatedSteamPartialPressure();

	return result;
}

double Injector::GetDryAirPressure() const
{
	auto result = _wrapper->GetAtmPressure() - GetSteamPressure();

	return result;
}

double Injector::GetMoistAirDensity() const
{
	//=(F8*1000/(287.058*(F2+273.15)))+(F7*1000/(461.495*(F2+273.15)))
	auto externalTemp = _wrapper->GetExternalTemp();
	auto result = GetDryAirPressure() * KILO / (_configuration->GetMoistAirDensityA() * (externalTemp + KELVIN)) + GetSteamPressure() * KILO / (_configuration->GetMoistAirDensityB() * (externalTemp + KELVIN));

	return result;
}

double Injector::GetChamberAirMass() const
{
	auto result = GetMoistAirDensity() * _configuration->GetChamberVolume() / KILO;

	return result;
}

double Injector::GetGasDensity() const
{
	//=F18*(F17*1000/F3)*(293.15/(F13+173.15))
	//
	//????
	//
	auto result = _configuration->GetNormalCondDensity() * (_sensors->GetReceiverPressure() * KILO / _wrapper->GetAtmPressure())*(KELVIN / (_wrapper->GetExternalTemp() + KELVIN));

	return result;
}

double Injector::GetGasConcentration() const
{
	//=(44.62*F16)/((1+0.00367*F2)*32.46)

	auto result = _configuration->GetUpMaxConcA() * _configuration->GetMolarMass() / ((1 + _configuration->GetUpMaxConcB() * _wrapper->GetExternalTemp()) * _configuration->GetUpMaxConcC());

	return result;
}

double Injector::GetDryAirMass() const
{
	auto result = _configuration->GetNormalCondDryDensity() * _configuration->GetChamberVolume() / KILO;

	return result;
}

double Injector::GetCorrectionCoefficient() const
{
	auto result = GetChamberAirMass() / (GetDryAirMass() * GetDryAirPressure() / _wrapper->GetAtmPressure());

	return result;
}

double Injector::GetInjectedPortion() const
{
	auto result = GetGasConcentration() * GetCorrectionCoefficient() * GetChamberAirMass();

	return result;
}

double Injector::GetValveArea() const
{
	auto result = M_PI * _configuration->GetValveBoreArea() * pow(_configuration->GetValveDiameter() * MILLI, 2);

	return result;
}

double Injector::GetGasFlowSpeed() const
{
	auto result = _configuration->GetGasFlowSpeedA() * sqrt(_configuration->GetGasFlowSpeedB() * (_wrapper->GetExternalTemp() + KELVIN) / _configuration->GetMolarMass());

	return result;
}

double Injector::GetGasFlow() const
{
	auto result = KILO * GetGasDensity() * _configuration->GetOutflowCoefficient() * GetGasFlowSpeed() * GetValveArea();

	return  result;
}



