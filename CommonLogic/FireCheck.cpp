#include "FireCheck.h"


 IArduinoWrapper* FireCheck::_staticWrapper;
 volatile unsigned long FireCheck::_micros;
 volatile unsigned long FireCheck::_rMicros;
 volatile bool FireCheck::_blastEngaged;
 volatile bool FireCheck::_fssOn;
 volatile bool FireCheck::_rssOn;
 volatile short FireCheck::_order;
 volatile short FireCheck::_digit;

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

	_staticWrapper = wrapper;
	InitSpeedCalculation();
}

CheckResult FireCheck::Check()
{
	if (IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}	

	_actuators->CheckHeater();

	const auto injTime = _injector->CalculateInjectionTime();

	if (IsRefreshCycle(REFRESH_CYCLE))
	{
		if (CheckCurrent(3) == Failed)
		{
			_screen->Println("Failed", 3);
			return Failed;
		}

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

		_screen->SetCursor(17, 0);
		_screen->PrintNumber(_digit);
		_screen->SetCursor(17, 1);
		_screen->PrintNumber(_order);

		const auto vlt = _actuators->GetHeaterSensorVoltage();
		_screen->SetCursor(0, 3);
		_screen->Print(BLANK_LINE);
		_screen->SetCursor(0, 3);
		_screen->PrintNumber(vlt, 2);
		_screen->Print(" v");

		if (_micros != 0 && _rMicros != 0)
		{
			const auto diff = _rMicros - _micros;
			const auto speed = SPEED_CONSTANT / static_cast<double>(diff == 0 ? 1 : diff) * 1000000;
			_screen->SetCursor(8, 3);
			_screen->PrintNumber(speed, 1);
			_screen->Print("m/s");
		}
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
		InitSpeedCalculation();
		_sensors->ResetDebouncingTriggers();

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
			_actuators->CycleValveExternal();
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

			_actuators->CycleValveInternal();			
		}

		if(_revCycleCounter < 20)
		{
			_revCycleCounter++;
		}
		else
		{
			_actuators->TurnFanOff();			
			_actuators->CloseBreech();			

			_wrapper->Delay(1500);

			_actuators->EngageInjectorDiode(true);
			_actuators->TurnIngnitionOn();
		}
	}	

	_cyclesCounter++;

	return Running;
}

void FireCheck::FssOn()
{
	_micros = _staticWrapper->GetMicroseconds();	
}

void FireCheck::RssOn()
{
	_rMicros = _staticWrapper->GetMicroseconds();	
}

void FireCheck::BlastOn()
{
	_blastEngaged = true;
}

void FireCheck::FssOnOrd()
{
	if (!_fssOn)
	{
		_micros = _staticWrapper->GetMicroseconds();
		_fssOn = true;
		_order = _order + _digit * 2;
		_digit *= 10;
	}
}

void FireCheck::RssOnOrd()
{
	if (!_rssOn)
	{
		_rMicros = _staticWrapper->GetMicroseconds();
		_rssOn = true;
		_order = _digit * 3 + _order;
		_digit *= 10;
	}
}

void FireCheck::BlastOnOrd()
{
	_blastEngaged = true;
	_order = _order + _digit;
	_digit *= 10;
}

void FireCheck::Stop() const
{
	_loader->Stop();
}

CheckResult FireCheck::CheckCurrent(char messageLine) const
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

	_screen->Println("Current: ", messageLine);
	_screen->PrintNumber(loaderCurrent, 2);
	_screen->Print(" a");

	return Passed;
}

void FireCheck::InitSpeedCalculation()
{
	_blastEngaged = false;
	_micros = 0;
	_rMicros = 0;	
	_fssOn = false;
	_rssOn = false;
	_digit = 1;
	_order = 0;
	/*Context::_fMicros = 0;
	Context::_rMicros = 0;
	Context::_order = 0;
	Context::_digit = 1;*/
}

