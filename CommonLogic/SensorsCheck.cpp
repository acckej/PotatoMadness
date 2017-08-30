#include "SensorsCheck.h"
#include "Constants.h"


SensorsCheck::SensorsCheck(IArduinoWrapper* wrapper, TestScreen* screen) : IHwCheck(wrapper, screen)
{	
	_shotSensors = true;
	_extEnv = false;
	_intEnv = false;
	_receiver = false;
}

CheckResult SensorsCheck::Check()
{
	if(_cyclesCounter == 0)
	{
		_screen->Refresh();
		_screen->Println("Sensor check", 1);
	}

	if(_shotSensors)
	{
		if(_cyclesCounter == 0)
		{
			_wrapper->ResetDebouncingTriggers();
		}
		else
		{
			auto blastSens = _wrapper->DigitalRead(BLAST_SENSOR_PORT);
			auto rss = _wrapper->DigitalRead(RSS_PORT);
			auto fss = _wrapper->DigitalRead(FSS_PORT);

			_screen->Println("Blast sens:", 2);
			_screen->Print(blastSens == ARDUINO_HIGH ? "1" : "0");
			_screen->Println("Rss:", 3);
			_screen->Print(rss == ARDUINO_HIGH ? "1" : "0");
			_screen->Print(" Fss:");
			_screen->Print(fss == ARDUINO_HIGH ? "1" : "0");

			if(blastSens || rss || fss)
			{
				_screen->Println("Incorrect state", 4);
				return Failed;
			}
		}

		if(_cyclesCounter >= 20)
		{
			_shotSensors = false;
			_extEnv = true;
			_screen->Refresh();
			_screen->Println("Ext sens check", 1);
			_cyclesCounter = 0;
		}
	}

	if(_extEnv)
	{
		if(_cyclesCounter == 0)
		{
			auto hum = _wrapper->GetExternalHumidity();
			auto temp = _wrapper->GetExternalTemp();

			_screen->Println("Hum:", 2);
			_screen->PrintNumber(hum, 2);
			_screen->Print(" Temp:");
			_screen->PrintNumber(temp, 2);

			if(hum == 0 || temp == 0)
			{
				_screen->Println("Ext sens err", 4);
				return Failed;
			}
		}
		else
		{
			if (_cyclesCounter >= 20)
			{
				_intEnv = true;
				_extEnv = false;
				_screen->Refresh();
				_screen->Println("Int sens check", 1);
				_cyclesCounter = 0;
			}
		}
	}

	if (_intEnv)
	{
		if (_cyclesCounter == 0)
		{
			auto press = _wrapper->GetAtmPressure();
			auto temp = _wrapper->GetInternalTemp();

			_screen->Println("Prsr:", 2);
			_screen->PrintNumber(press, 2);
			_screen->Print(" Temp:");
			_screen->PrintNumber(temp, 2);

			if (press == 0 || temp == 0)
			{
				_screen->Println("Int sens err", 4);
				return Failed;
			}
		}
		else
		{
			if (_cyclesCounter >= 20)
			{
				_intEnv = false;
				_receiver = true;
				_screen->Refresh();
				_screen->Println("Receiver pressure", 1);
				_cyclesCounter = 0;
			}
		}
	}

	if (_receiver)
	{
		if (_cyclesCounter == 0)
		{
			auto press = _wrapper->GetReceiverPressure();			
			_screen->Println("Pressure:", 2);
			_screen->PrintNumber(press, 2);			

			if (press < 0)
			{
				_screen->Println("Rcv sens err", 3);
				return Failed;
			}
		}
		else
		{
			if (_cyclesCounter >= 20)
			{				
				_cyclesCounter = 0;
				return Passed;
			}
		}
	}

	_wrapper->Delay(100);

	return Running;
}


