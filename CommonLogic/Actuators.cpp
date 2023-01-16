#include "Actuators.h"
#include "Constants.h"
#include "TypeDefinitions.h"


Actuators::Actuators(IArduinoWrapper *wrapper)
{
	_wrapper = wrapper;
	_fanOn = false;
	_heaterOn = false;
	_breechOpened = false;
	_ignitionOn = false;
	_injectorStarted = false;
	_cycleValveExternal = true;
}

void Actuators::OpenBreech() 
{
	_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_HIGH);
	_breechOpened = true;
}

void Actuators::CloseBreech() 
{
	_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_HIGH);
	_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_LOW);
	_breechOpened = false;
}

void Actuators::DisableBreech() const
{
	_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_LOW);
}

void Actuators::TurnFanOn() 
{
	_wrapper->DigitalWrite(FAN_PORT, ARDUINO_LOW);
	_fanOn = true;
}

void Actuators::TurnFanOff() 
{
	_wrapper->DigitalWrite(FAN_PORT, ARDUINO_HIGH);
	_fanOn = false;
}

void Actuators::TurnIngnitionOn() 
{
	_wrapper->DigitalWrite(IGNITION_PORT, ARDUINO_LOW );
	_ignitionOn = true;
}

void Actuators::TurnIgnitionOff() 
{
	_wrapper->DigitalWrite(IGNITION_PORT, ARDUINO_HIGH);
	_ignitionOn = false;
}

void Actuators::InjectorStart() 
{
	_wrapper->DigitalWrite(INJECTOR_PORT, ARDUINO_HIGH);
	_injectorStarted = true;
}

void Actuators::InjectorStop() 
{
	_wrapper->DigitalWrite(INJECTOR_PORT, ARDUINO_LOW);
	_injectorStarted = false;
}

void Actuators::CheckHeater() 
{
	const auto vlt = GetHeaterSensorVoltage();

	if(vlt >= HEATER_VOLTAGE_MAX || 
		vlt <= HEATER_VOLTAGE_LIMIT)
	{
		_wrapper->DigitalWrite(HEATER_PORT, ARDUINO_HIGH);
		_heaterOn = false;
		return;
	}

	if(vlt >= HEATER_VOLTAGE_THR)
	{
		_wrapper->DigitalWrite(HEATER_PORT, ARDUINO_LOW);
		_heaterOn = true;
	}	
}

void Actuators::HeaterOff() 
{
	_wrapper->DigitalWrite(HEATER_PORT, ARDUINO_HIGH);
	_heaterOn = false;
}

void Actuators::TurnMixingFanOn()
{
	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_ONE, ARDUINO_HIGH);
	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_TWO, ARDUINO_HIGH);
}

void Actuators::TurnMixingFanOff()
{
	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_ONE, ARDUINO_LOW);
	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_TWO, ARDUINO_LOW);
}

//void Actuators::CycleValveExternal()
//{
//	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_ONE, ARDUINO_HIGH);
//	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_TWO, ARDUINO_HIGH);
//	_wrapper->Delay(CYCLE_VALVE_DELAY);
//	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_ONE, ARDUINO_LOW);
//}
//
//void Actuators::CycleValveInternal()
//{
//	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_ONE, ARDUINO_LOW);
//	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_TWO, ARDUINO_LOW);
//	_wrapper->Delay(CYCLE_VALVE_DELAY);
//	_wrapper->DigitalWrite(CYCLE_VALVE_PORT_ONE, ARDUINO_HIGH);
//}

void Actuators::EngageInjectorDiode(bool on) const
{
	_wrapper->DigitalWrite(INJ_LED_PORT, on ? ARDUINO_HIGH : ARDUINO_LOW);
}

bool Actuators::IsCycleValveExternal()
{
	return _cycleValveExternal;
}

bool Actuators::FanOn() const
{
	return _fanOn;
}

bool Actuators::IgnitionOn() const
{
	return _ignitionOn;
}

bool Actuators::InjectorStarted() const
{
	return _injectorStarted;
}

bool Actuators::AuxEnabled() const
{
	return _heaterOn;
}

bool Actuators::BreechOpened() const
{
	return _breechOpened;
}

float Actuators::GetHeaterSensorVoltage() const
{
	const auto volt = _wrapper->AnalogRead(HEATER_SENSOR_PORT);
	const auto val = static_cast<float>(volt) * static_cast<float>(ANALOG_COEFFICIENT);

	return val;
}

