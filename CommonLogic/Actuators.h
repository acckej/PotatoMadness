#pragma once
#include "IArduinoWrapper.h"

class Actuators
{
public:
	Actuators(IArduinoWrapper* wrapper);
	
	void OpenBreach() const;
	void CloseBreach() const;
	void DisableBreach() const;

	void TurnFanOn() const;
	void TurnFanOff() const;

	void IngnitionOn() const;
	void IgnitionOff() const;

	void InjectorStart() const;
	void InjectorStop() const;

	void EngageInjectorDiode(bool on) const;

private:
	IArduinoWrapper* _wrapper;
};

