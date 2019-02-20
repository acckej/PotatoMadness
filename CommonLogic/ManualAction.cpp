#include "ManualAction.h"

ManualAction::ManualAction(IArduinoWrapper* wrapper, Loader* loader, Actuators* actuators, Sensors* sensors, ManualScreen* screen) : IAction(wrapper, nullptr),
_fanStarted(0), _loaderStarted(0), _ignitionStarted(0), _breechStarted(0)
{
	_actuators = actuators;
	_loader = loader;
	_sensors = sensors;	
	_screen = screen;
}

ManualAction::~ManualAction()
{
}

ActionState ManualAction::Execute()
{
	CheckLoaderState();
	CheckBreechButton();
	CheckFanButtons();
	CheckIgnitionButton();
	CheckInjectorButton();
	CheckFanButtons();

	if(_loader->IsOverload())
	{
		_errorCode = LoaderOverload;
		return Error;
	}

	if(_sensors->GetBatteryVoltage() < LOW_VOLTAGE)
	{
		_errorCode = LowVoltage;
		return Error;
	}

	if(Context::GetButtonsController().AreButtonsPressed(x1A, x2B))
	{
		Context::Halt();
		return Completed;
	}

	return Executing;
}

const char* ManualAction::GetActionName()
{
	return "ManualMode";
}

void ManualAction::CheckLoaderButtons()
{
	auto btn = Context::GetButtonsController().GetPressedButton();
	if(btn != x1A && btn != x2B)
	{
		return;
	}

	auto current = _wrapper->GetMilliseconds();

	if (current - _loaderStarted < BUTTONS_DELAY)
	{
		return;
	}

	_loaderStarted = current;

	if(btn == x1A && (_firingState == Reversed || _firingState == FrontRev)) //fwd
	{
		_firingState = RevFront;
		_loader->Forward();
		return;
	}

	if (btn == x2B && (_firingState == Front || _firingState == RevFront)) //rev
	{
		_firingState = FrontRev;
		_loader->Reverse();		
	}
}

void ManualAction::CheckLoaderState()
{
	if(_loader->IsFwCheckOn())
	{
		_firingState = Front;
		return;
	}

	if(_loader->IsRevCheckOn())
	{
		_firingState = Reversed;
	}
}

void ManualAction::CheckBreechButton()
{
	auto btn = Context::GetButtonsController().GetPressedButton();

	if(btn != x3C)
	{
		return;
	}

	auto current = _wrapper->GetMilliseconds();

	if (current - _loaderStarted < BUTTONS_DELAY)
	{
		return;
	}

	_breechStarted = current;

	if(_actuators->BreechOpened())
	{
		_actuators->CloseBreech();
		return;
	}

	_actuators->TurnIgnitionOff();
	_actuators->OpenBreech();	
}

void ManualAction::CheckFanButtons()
{
	auto btn = Context::GetButtonsController().GetPressedButton();

	if (btn != x4D)
	{
		return;
	}

	auto current = _wrapper->GetMilliseconds();

	if (current - _loaderStarted < BUTTONS_DELAY)
	{
		return;
	}

	_fanStarted = current;

	if(_actuators->FanOn())
	{
		_actuators->TurnFanOff();
		return;
	}

	_actuators->TurnFanOn();
}

void ManualAction::CheckInjectorButton() const
{
	auto btn = Context::GetButtonsController().GetPressedButton();

	if(btn != x5E)
	{
		_actuators->InjectorStop();
		_actuators->EngageInjectorDiode(false);
		return;
	}

	if (!_actuators->InjectorStarted())
	{
		_actuators->InjectorStart();
		_actuators->EngageInjectorDiode(true);
	}
}

void ManualAction::CheckIgnitionButton()
{
	auto btn = Context::GetButtonsController().GetPressedButton();

	if (btn != x6F)
	{
		return;
	}

	auto current = _wrapper->GetMilliseconds();

	if (current - _loaderStarted < BUTTONS_DELAY)
	{
		return;
	}

	_ignitionStarted = current;

	if(_actuators->BreechOpened())
	{
		return;
	}

	if(_actuators->IgnitionOn())
	{
		_actuators->TurnIgnitionOff();
		return;
	}

	_actuators->TurnIngnitionOn();
}
