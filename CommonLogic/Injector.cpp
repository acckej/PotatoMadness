#include "Injector.h"
#include <math.h>
#include "CalculationConstants.h"
#include "Constants.h"


Injector::Injector(IConfiguration* config, IArduinoWrapper* wrapper, Sensors* sensors)
{
	_configuration = config;
	_wrapper = wrapper;
	_sensors = sensors;
}

unsigned long Injector::CalculateInjectionTime() const
{
	auto gasFlow = GetGasFlow();
	auto time = KILO * GetInjectedPortion() / (gasFlow == 0.0 ? 1 : gasFlow);	
	time = ceil(time * _configuration->GetCorrectionalCoef());
	return time > MAX_INJECTION_TIME ? MAX_INJECTION_TIME : static_cast<unsigned long>(time);	
}

double Injector::GetSaturatedSteamPartialPressure() const
{
	//=0.61078*10^(((7.5*(F2+273.15))-2048.625)/((F2+273.15)-35.85))
	const auto externalTemp = static_cast<double>(_wrapper->GetExternalTemp() + KELVIN);
	const auto result = pow(_configuration->GetSsPpA() * 10, (_configuration->GetSsPpB() * externalTemp - _configuration->GetSsPpC()) / (externalTemp - _configuration->GetSsPpD()));

	return result;
}

double Injector::GetSteamPressure() const
{
	const auto result = static_cast<double>(_wrapper->GetExternalHumidity()) * GetSaturatedSteamPartialPressure();

	return result;
}

double Injector::GetDryAirPressure() const
{
	const auto result = static_cast<double>(_wrapper->GetAtmPressure()) - GetSteamPressure();

	return result;
}

double Injector::GetMoistAirDensity() const
{
	//=(F8*1000/(287.058*(F2+273.15)))+(F7*1000/(461.495*(F2+273.15)))
	//KILO ?

	const auto externalTemp = static_cast<double>(_wrapper->GetExternalTemp() + KELVIN);
	//const auto result = GetDryAirPressure() * KILO / (_configuration->GetMoistAirDensityA() * externalTemp) + GetSteamPressure() * KILO / (_configuration->GetMoistAirDensityB() * externalTemp);

	const auto result = GetDryAirPressure() / (_configuration->GetMoistAirDensityA() * externalTemp) + GetSteamPressure() / (_configuration->GetMoistAirDensityB() * externalTemp);


	return result;
}

double Injector::GetChamberAirMass() const
{
	const auto result = GetMoistAirDensity() * _configuration->GetChamberVolume() / static_cast<double>(KILO);

	return result;
}

double Injector::GetGasDensity() const
{
	//=F18*(F17*1000/F3)*(293.15/(F13+173.15))
	//
	//????
	//
	const auto externalTemp = static_cast<double>(_wrapper->GetExternalTemp() + KELVIN);
	const auto result = _configuration->GetNormalCondDensity() * (_sensors->GetReceiverPressure() / static_cast<double>(_wrapper->GetAtmPressure())) * (static_cast<double>((KELVIN + NORMAL_TEMP_C)) / externalTemp);

	return result;
}

double Injector::GetGasConcentration() const
{
	//molar mass?
	//=(44.62*F16)/((1+0.00367*F2)*32.46)
	const auto externalTemp = static_cast<double>(_wrapper->GetExternalTemp() + KELVIN);

	const auto result = _configuration->GetUpMaxConcA() * _configuration->GetMolarMass() * MILLI / ((1 + _configuration->GetUpMaxConcB() * externalTemp) * _configuration->GetUpMaxConcC());

	return result;
}

double Injector::GetDryAirMass() const
{
	const auto result = _configuration->GetNormalCondDryDensity() * _configuration->GetChamberVolume() / KILO;

	return result;
}

double Injector::GetCorrectionCoefficient() const
{
	const auto result = GetChamberAirMass() / (GetDryAirMass() * GetDryAirPressure() / static_cast<double>(_wrapper->GetAtmPressure()));

	return result;
}

double Injector::GetInjectedPortion() const
{
	const auto result = GetGasConcentration() * GetCorrectionCoefficient() * GetChamberAirMass();

	return result;
}

double Injector::GetValveArea() const
{
	//const auto result = M_PI * _configuration->GetValveBoreArea() * pow(_configuration->GetValveDiameter() * MILLI, 2);

	const auto result = M_PI * pow(_configuration->GetValveDiameter() / 2 * MILLI, 2);

	return result;
}

double Injector::GetGasFlowSpeed() const
{
	const auto externalTemp = static_cast<double>(_wrapper->GetExternalTemp() + KELVIN);
	const auto result = _configuration->GetGasFlowSpeedA() * sqrt(_configuration->GetGasFlowSpeedB() * externalTemp / _configuration->GetMolarMass());

	return result;
}

double Injector::GetGasFlow() const
{
	// KILO?
	const auto result = GetGasDensity() * _configuration->GetOutflowCoefficient() * GetGasFlowSpeed() * GetValveArea();

	return  result;
}



