#include "SensorsCheck.h"

#define REFRESH_CYCLE 500

SensorsCheck::SensorsCheck(IArduinoWrapper* wrapper, TestScreen* screen, Loader* loader, Actuators* actuators, Sensors* sensors) : IHwCheck(wrapper, screen)
{	
	_shotSensors = true;
	_extEnv = false;
	_intEnv = false;
	_receiver = false;
	_ammoSensor = false;
	_loader = loader;
	_actuators = actuators;
	_sensors = sensors;
}

CheckResult SensorsCheck::Check()
{
	if(IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}

	if(_shotSensors)
	{
		if(_cyclesCounter == 0)
		{
			_screen->Refresh();
			_screen->Println("Sensor check", 1);
			_actuators->EngageInjectorDiode(true);
			_sensors->ResetDebouncingTriggers();
		}
		else
		{
			auto blastSens = _sensors->GetBlastSensorState();
			auto rss = _sensors->GetRss();
			auto fss = _sensors->GetFss();
			auto fail = false;

			if(blastSens || rss || fss)
			{
				_screen->Println("Incorrect state", 4);
				fail = true;
			}

			if (IsRefreshCycle(REFRESH_CYCLE) || fail)
			{
				_screen->Println("Blast sens:", 2);
				_screen->Print(blastSens ? "1" : "0");
				_screen->Println("Rss:", 3);
				_screen->Print(rss ? "1" : "0");
				_screen->Print(" Fss:");
				_screen->Print(fss ? "1" : "0");
			}

			if(fail)
			{
				return Failed;
			}
		}

		_cyclesCounter++;

		if(_cyclesCounter >= 40)
		{
			_shotSensors = false;
			_extEnv = true;			
			_cyclesCounter = 0;
		}
	}

	if(_extEnv)
	{
		if(_cyclesCounter == 0)
		{
			_screen->Refresh();
			_screen->Println("Ext sens check", 1);	
			_actuators->EngageInjectorDiode(false);
			_cyclesCounter++;
		}
		else
		{
			auto hum = _wrapper->GetExternalHumidity();
			auto temp = _wrapper->GetExternalTemp();

			if (IsRefreshCycle(REFRESH_CYCLE))
			{
				_screen->Println("Hum:", 2);
				_screen->PrintNumber(hum, 2);
				_screen->Print(" Temp:");
				_screen->PrintNumber(temp, 2);
			}

			if (hum == 0 || temp == 0)
			{
				_screen->Println("Ext sens err", 4);
				return Failed;
			}

			_cyclesCounter++;

			if (_cyclesCounter >= 40)
			{
				_intEnv = true;
				_extEnv = false;				
				_cyclesCounter = 0;
			}
		}
	}

	if (_intEnv)
	{
		if (_cyclesCounter == 0)
		{
			_screen->Refresh();
			_screen->Println("Int sens check", 1);
			_actuators->EngageInjectorDiode(true);
			_cyclesCounter++;
		}
		else
		{
			auto press = _wrapper->GetAtmPressure();
			auto temp = _wrapper->GetInternalTemp();

			if (IsRefreshCycle(REFRESH_CYCLE))
			{
				_screen->Println("Prsr:", 2);
				_screen->PrintNumber(press, 2);
				_screen->Print(" Temp:");
				_screen->PrintNumber(temp, 2);
			}

			if (press == 0 || temp == 0)
			{
				_screen->Println("Int sens err", 4);
				return Failed;
			}

			_cyclesCounter++;

			if (_cyclesCounter >= 40)
			{
				_intEnv = false;
				_receiver = true;
				_cyclesCounter = 0;
			}
		}
	}

	if (_receiver)
	{
		if (_cyclesCounter == 0)
		{
			_screen->Refresh();
			_screen->Println("Receiver pressure", 1);	
			_actuators->EngageInjectorDiode(false);
			_cyclesCounter++;
		}
		else
		{
			auto press = _sensors->GetReceiverPressure();
			if (IsRefreshCycle(REFRESH_CYCLE))
			{
				_screen->Println("Pressure:", 2);
				_screen->PrintNumber(press, 2);
			}

			if (press < 0)
			{
				_screen->Println("Rcv sens err", 3);
				return Failed;
			}

			_cyclesCounter++;

			if (_cyclesCounter >= 40)
			{		
				_receiver = false;
				_ammoSensor = true;
				_cyclesCounter = 0;				
			}
		}
	}

	if (_ammoSensor)
	{
		if (_cyclesCounter == 0)
		{
			_screen->Refresh();
			_screen->Println("Ammo sensor", 1);
			_actuators->EngageInjectorDiode(true);
			_cyclesCounter++;
		}
		else
		{
			auto as = _loader->NoAmmo();
			if (IsRefreshCycle(REFRESH_CYCLE))
			{
				_screen->Println("Ammo: ", 2);
				_screen->Print(as ? "1" : "0");
			}

			_cyclesCounter++;

			if (_cyclesCounter >= 40)
			{
				_actuators->EngageInjectorDiode(false);
				_ammoSensor = false;
				_cyclesCounter = 0;
				_screen->Println("Passed", 4);
				return Passed;
			}
		}
	}

	//_wrapper->Delay(100);

	return Running;
}


