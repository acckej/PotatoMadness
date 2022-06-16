#pragma once

#include "Configuration.h"
#include "IArduinoWrapper.h"
#include "Sensors.h"

class Injector
{
public:
	Injector(IConfiguration* config, IArduinoWrapper* wrapper, Sensors* sensors);

	unsigned long CalculateInjectionTime() const;
//private:
	double GetSaturatedSteamPartialPressure() const;
	double GetSteamPressure() const;
	double GetDryAirPressure() const;
	double GetMoistAirDensity() const;
	double GetChamberAirMass() const;
	double GetGasDensity() const;
	double GetGasConcentration() const;
	double GetDryAirMass() const;
	double GetCorrectionCoefficient() const;
	double GetInjectedPortion() const;
	double GetValveArea() const;
	double GetGasFlowSpeed() const;
	double GetGasFlow() const;


	IConfiguration* _configuration;
	IArduinoWrapper* _wrapper;
	Sensors* _sensors;
};

