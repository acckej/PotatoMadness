#include "Actuators.h"
#include "Constants.h"
#include "TypeDefinitions.h"


Actuators::Actuators(IArduinoWrapper *wrapper)
{
	_wrapper = wrapper;
	_fanOn = false;
	_auxOn = false;
	_breechOpened = false;
	_ignitionOn = false;
	_injectorStarted = false;
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

void Actuators::AuxOn() 
{
	_wrapper->DigitalWrite(RESERVED_RELAY_PORT, ARDUINO_LOW);
	_auxOn = true;
}

void Actuators::AuxOff() 
{
	_wrapper->DigitalWrite(RESERVED_RELAY_PORT, ARDUINO_HIGH);
	_auxOn = false;
}

void Actuators::EngageInjectorDiode(bool on) const
{
	_wrapper->DigitalWrite(INJ_LED_PORT, on ? ARDUINO_HIGH : ARDUINO_LOW);
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
	return _auxOn;
}

bool Actuators::BreechOpened() const
{
	return _breechOpened;
}

