#include "FireCheck.h"


 IArduinoWrapper* FireCheck::_staticWrapper;
 volatile unsigned long FireCheck::_millis;
 volatile bool FireCheck::_blastEngaged;
 volatile bool FireCheck::_fssOn;
 volatile bool FireCheck::_rssOn;

FireCheck::FireCheck(IArduinoWrapper* wrapper, 
	TestScreen* screen, 
	Loader* loader, 
	Actuators* actuators, 
	Sensors* sensors, 
	ButtonsController* buttons,
	Injector* injector) : IHwCheck(wrapper, screen)
{
	_actuators = actuators;
	_buttons = buttons;
	_loader = loader;
	_sensors = sensors;
	_injector = injector;

	_breechOpen = false;
	_injecting = false;

	_actuators->CloseBreech();
	_actuators->TurnIgnitionOff();

	_isFwCycle = false;
	_isRevCycle = false;

	_fwCycleCounter = 0;
	_revCycleCounter = 0;

	_blastEngaged = false;
	_millis = 0;
	_staticWrapper = wrapper;
	_fssOn = false;
	_rssOn = false;
}

CheckResult FireCheck::Check()
{
	if (IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}

	if (CheckCurrent(3) == Failed)
	{
		_screen->Println("Failed", 3);
		return Failed;
	}

	_actuators->CheckHeater();

	const auto injTime = _injector->CalculateInjectionTime();

	_screen->SetCursor(0, 0);
	_screen->Print(BLANK_LINE);
	_screen->SetCursor(0, 0);
	_screen->PrintNumber(injTime);
	_screen->Print(" ms");

	const auto press = _sensors->GetReceiverPressure();
	_screen->SetCursor(0, 1);
	_screen->Print(BLANK_LINE);
	_screen->SetCursor(0, 1);
	_screen->PrintNumber(press, 2);
	_screen->Print(" pa");

	const auto vlt = _actuators->GetHeaterSensorVoltage();
	_screen->SetCursor(0, 3);
	_screen->Print(BLANK_LINE);
	_screen->SetCursor(0, 3);
	_screen->PrintNumber(vlt, 2);
	_screen->Print(" v");

	if (_blastEngaged && _millis != 0)
	{
		auto speed = (SPEED_CONSTANT / _millis) * 1000;
		_screen->SetCursor(8, 3);		
		_screen->PrintNumber(speed, 7);
	}

	if (_loader->IsRevCheckOn() && _buttons->IsButtonPressed(x1A))
	{
		_loader->Forward();
	}

	if (_loader->IsFwCheckOn() && _buttons->IsButtonPressed(x2B))
	{
		_loader->Reverse();
	}

	if(_buttons->IsButtonPressed(x3C))
	{
		_blastEngaged = 0;
		_millis = 0;
		_sensors->ResetDebouncingTriggers();
		_fssOn = false;
		_rssOn = false;

		if (!_injecting)
		{
			_injecting = true;
			_actuators->InjectorStart();
			_wrapper->Delay(injTime);
			_actuators->InjectorStop();
		}
	}
	else
	{
		_injecting = false;
	}

	/*if (_buttons->IsButtonPressed(x3C))
	{
		_actuators->InjectorStart();
	}
	else
	{
		_actuators->InjectorStop();
	}*/

	if(_buttons->IsButtonPressed(x4D))
	{
		Stop();
		return Passed;
	}

	if (_loader->IsFwCheckOn())
	{
		if (!_isFwCycle)
		{
			_isFwCycle = true;
			_isRevCycle = false;
			_fwCycleCounter = 0;

			_actuators->EngageInjectorDiode(false);
			_actuators->TurnIgnitionOff();
			_actuators->OpenBreech();
			_actuators->TurnFanOn();
		}

		if (_fwCycleCounter > 30)
		{
			_fwCycleCounter = 0;
			_actuators->CloseBreech();
			_actuators->TurnFanOff();
		}
		else
		{
			_fwCycleCounter++;
		}
	}	

	if(_loader->IsRevCheckOn())
	{
		if (!_isRevCycle)
		{
			_isRevCycle = true;
			_isFwCycle = false;
			_revCycleCounter = 0;

			_actuators->CloseBreech();
		}

		if(_revCycleCounter < 20)
		{
			_revCycleCounter++;
		}
		else
		{
			_actuators->EngageInjectorDiode(true);
			_actuators->TurnIngnitionOn();
		}
	}	

	_cyclesCounter++;

	return Running;
}

void FireCheck::FssOn()
{
	if (_blastEngaged && !_fssOn)
	{
		_millis = _staticWrapper->GetMilliseconds();
		_fssOn = true;
	}
}

void FireCheck::RssOn()
{
	if (_blastEngaged && !_rssOn)
	{
		auto millis = _staticWrapper->GetMilliseconds();
		_millis = millis - _millis;
		_rssOn = true;
	}
}

void FireCheck::BlastOn()
{
	_blastEngaged = true;
}

void FireCheck::Stop() const
{
	_loader->Stop();
}

CheckResult FireCheck::CheckCurrent(char messageLine)
{
	const auto loaderCurrent = static_cast<double>(_loader->GetCurrent());

	if (loaderCurrent > LOADER_CURRENT_MAX)
	{
		Stop();
		_screen->Println("Overload: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print(" a");

		return Failed;
	}

	if (IsRefreshCycle(REFRESH_CYCLE))
	{
		_screen->Println("Current: ", messageLine);
		_screen->PrintNumber(loaderCurrent, 2);
		_screen->Print(" a");
	}

	return Passed;
}

