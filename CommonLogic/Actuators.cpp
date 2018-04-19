#include "Actuators.h"
#include "Constants.h"
#include "TypeDefinitions.h"


Actuators::Actuators(IArduinoWrapper *wrapper)
{
	_wrapper = wrapper;
}

void Actuators::OpenBreech() const
{
	_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_HIGH);
}

void Actuators::CloseBreech() const
{
	_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_HIGH);
	_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_LOW);
}

void Actuators::DisableBreach() const
{
	_wrapper->DigitalWrite(BREACH_OPEN_PORT, ARDUINO_LOW);
	_wrapper->DigitalWrite(BREACH_CLOSE_PORT, ARDUINO_LOW);
}

void Actuators::TurnFanOn() const
{
	_wrapper->DigitalWrite(FAN_PORT, ARDUINO_LOW);
}

void Actuators::TurnFanOff() const
{
	_wrapper->DigitalWrite(FAN_PORT, ARDUINO_HIGH);
}

void Actuators::IngnitionOn() const
{
	_wrapper->DigitalWrite(IGNITION_PORT, ARDUINO_LOW );
}

void Actuators::IgnitionOff() const
{
	_wrapper->DigitalWrite(IGNITION_PORT, ARDUINO_HIGH);
}

void Actuators::InjectorStart() const
{
	_wrapper->DigitalWrite(INJECTOR_PORT, ARDUINO_HIGH);
}

void Actuators::InjectorStop() const
{
	_wrapper->DigitalWrite(INJECTOR_PORT, ARDUINO_LOW);
}

void Actuators::AuxOn() const
{
	_wrapper->DigitalWrite(RESERVED_RELAY_PORT, ARDUINO_LOW);
}

void Actuators::AuxOff() const
{
	_wrapper->DigitalWrite(RESERVED_RELAY_PORT, ARDUINO_HIGH);
}

void Actuators::EngageInjectorDiode(bool on) const
{
	_wrapper->DigitalWrite(INJ_LED_PORT, on ? ARDUINO_HIGH : ARDUINO_LOW);
}

