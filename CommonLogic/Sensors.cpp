#include "Sensors.h"
#include "Constants.h"

Sensors::Sensors(IArduinoWrapper* wrapper)
{
	_wrapper = wrapper;
}

double Sensors::GetBatteryVoltage() const
{
	auto vlt = _wrapper->AnalogRead(VOLTAGE_PORT);
	auto calculated = static_cast<double>(vlt) * ANALOG_COEFFICIENT * VOLTAGE_COEFFICIENT;

	return calculated;
}


float Sensors::GetReceiverPressure() const
{
	auto press = _wrapper->AnalogRead(RECEIVER_PRESSURE_PORT);
	auto val = float(press) * ANALOG_COEFFICIENT;

	if (val < 0.45f)
	{
		return -1;
	}

	val = float(val - PRESSURE_CONSTANT) * PRESSURE_COEFFICIENT;

	return val < 0 ? val * -1 : val;
}

void Sensors::ResetDebouncingTriggers() const
{
	_wrapper->DigitalWrite(BLAST_TRIGGER_RESET_PORT, ARDUINO_HIGH);
	_wrapper->DigitalWrite(SS_TRIGGER_RESET_PORT, ARDUINO_LOW);
	_wrapper->Delay(100);
	_wrapper->DigitalWrite(BLAST_TRIGGER_RESET_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(SS_TRIGGER_RESET_PORT, ARDUINO_HIGH);
}

bool Sensors::GetFss() const
{
	auto result = _wrapper->DigitalRead(FSS_PORT);
	return result == ARDUINO_HIGH;
}

bool Sensors::GetRss() const
{
	auto result = _wrapper->DigitalRead(RSS_PORT);
	return result == ARDUINO_HIGH;
}

bool Sensors::GetBlastSensorState() const
{
	auto result = _wrapper->DigitalRead(BLAST_SENSOR_PORT);
	return result == ARDUINO_HIGH;
}


