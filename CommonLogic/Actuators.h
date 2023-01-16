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

	void TurnIngnitionOn();
	void TurnIgnitionOff();

	void InjectorStart();
	void InjectorStop();

	void CheckHeater();
	void HeaterOff();

	/*void CycleValveExternal();
	void CycleValveInternal();*/
	void TurnMixingFanOn();
	void TurnMixingFanOff();

	void EngageInjectorDiode(bool on) const;

	bool IsCycleValveExternal();
	bool FanOn() const;
	bool IgnitionOn() const;
	bool InjectorStarted() const;
	bool AuxEnabled() const;
	bool BreechOpened() const;

	float GetHeaterSensorVoltage() const;
private:
	IArduinoWrapper* _wrapper;
	bool _fanOn;
	bool _ignitionOn;
	bool _injectorStarted;
	bool _heaterOn;
	bool _breechOpened;
	bool _cycleValveExternal;
};

