#pragma once
#include "IArduinoWrapper.h"

class Actuators
{
public:
	Actuators(IArduinoWrapper* wrapper);
	
	void OpenBreech();
	void CloseBreech();
	void DisableBreech() const;

	void TurnFanOn();
	void TurnFanOff();

	void IngnitionOn();
	void IgnitionOff();

	void InjectorStart();
	void InjectorStop();

	void AuxOn();
	void AuxOff();

	void EngageInjectorDiode(bool on) const;

	bool FanOn() const;
	bool IgnitionOn() const;
	bool InjectorStarted() const;
	bool AuxEnabled() const;
	bool BreechOpened() const;
private:
	IArduinoWrapper* _wrapper;
	bool _fanOn;
	bool _ignitionOn;
	bool _injectorStarted;
	bool _auxOn;
	bool _breechOpened;
};

