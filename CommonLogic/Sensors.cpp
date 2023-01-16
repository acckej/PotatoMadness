#include "Sensors.h"

//#include "CalculationConstants.h"
#include "CalculationConstants.h"
#include "Constants.h"
#include "TypeDefinitions.h"

Sensors::Sensors(IArduinoWrapper* wrapper) : _wrapper(wrapper)
{
}

double Sensors::GetBatteryVoltage() const
{
	const auto vlt = _wrapper->AnalogRead(VOLTAGE_PORT);
	const auto calculated = static_cast<double>(vlt) * static_cast<double>(ANALOG_COEFFICIENT) * static_cast<double>(VOLTAGE_COEFFICIENT);

	return calculated;
}


double Sensors::GetReceiverPressure() const
{
	//todo: 
	const auto press = _wrapper->AnalogRead(RECEIVER_PRESSURE_PORT);
	auto val = static_cast<double>(press) * static_cast<double>(ANALOG_COEFFICIENT);

	if (val < static_cast<double>(0.45f))
	{
		return (double) - 1.0f;
	}

	val = (val - static_cast<double>(PRESSURE_CONSTANT)) * static_cast<double>(PRESSURE_COEFFICIENT) * KILO;

	return val < static_cast<double>(0.0f) ? val * static_cast<double>(- 1.0f) : val;

	//return 400000.0f;//176000.0f;
}

void Sensors::ResetDebouncingTriggers() const
{
	_wrapper->DigitalWrite(BLAST_TRIGGER_RESET_PORT, ARDUINO_HIGH);
	_wrapper->Delay(10);
	_wrapper->DigitalWrite(BLAST_TRIGGER_RESET_PORT, ARDUINO_LOW);
}

bool Sensors::GetFss() const
{
	const auto result = _wrapper->DigitalRead(FSS_PORT);
	return result == ARDUINO_HIGH;
}

bool Sensors::GetRss() const
{
	const auto result = _wrapper->DigitalRead(RSS_PORT);
	return result == ARDUINO_HIGH;
}

bool Sensors::GetBlastSensorState() const
{
	const auto result = _wrapper->DigitalRead(BLAST_SENSOR_PORT);
	return result == ARDUINO_HIGH;
}


