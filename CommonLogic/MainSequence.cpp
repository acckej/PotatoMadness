#include "MainSequence.h"
#include "LoaderForwardAction.h"
#include "Context.h"
#include "PrepareForFiringAction.h"
#include "LoaderReverseAction.h"
#include "LoaderReverseActionForcedMixing.h"
#include "BatteryCheck.h"
#include "ButtonsCheck.h"
#include "LoaderCheck.h"
#include "MachineryCheck.h"
#include "SensorsCheck.h"


MainSequence::MainSequence(IArduinoWrapper* wrapper)
{
	_wrapper = wrapper;

	_checks = nullptr;
	_firingActions = nullptr;
	_firingActionsForcedMixing = nullptr;
	_firingController = nullptr;
	_firingScreen = nullptr;
	_firingSequencer = nullptr;
	_hwChecksSequence = nullptr;
	_injector = nullptr;
	_testScreen = nullptr;
	_mainScreen = nullptr;
	_injectorTestScreen = nullptr;
	_configScreen = nullptr;
	_waitingForInput = false;		
	_readyToSwitch = false;
	
}

MainSequence::~MainSequence()
{
	CleanupFiringSequences();
	CleanupConfigEdit();
	CleanupHwChecks();
	CleanupMainMenu();
}

SystemState MainSequence::Run()
{
	if(Context::IsMainScreenRequested())
	{
		SwitchMode(MainMenu);		
		return SystemIdle;
	}

	switch (Context::GetOperationMode())
	{
	case MainMenu:
		{
			return RunMainMenu();
		}
	case ConfigEditScreen:
		{
			return RunConfigEdit();
		}
	case FiringMode:
	case FiringModeForcedMixing:
		{
			return RunFiringSequence();
		}
	case TestMode:
		{
			return RunHwChecks();
		}
	default: ;
	}

	return SystemRunning;
}

void MainSequence::Init()
{
	auto curr = Context::GetOperationMode();
	if(curr != MainMenu)
	{
		SwitchMode(MainMenu);
	}
	else
	{
		InitializeMainMenu();
	}
}

void MainSequence::InitializeFiringSequence()
{
	_firingActions = new IAction*[FIRING_ACTIONS_COUNT];
	_firingActionsForcedMixing = new IAction*[FIRING_ACTIONS_COUNT];

	_firingController = new FiringController(_wrapper);
	_injector = new Injector(Context::GetConfiguration(), _wrapper, Context::GetSensors());

	_firingScreen = new FiringScreen(_wrapper);
	_firingScreen->Refresh();

	_firingActions[2] = new PrepareForFiringAction(_wrapper, _firingController, Context::GetActuators(), Context::GetSensors(), nullptr, _firingScreen);
	_firingActions[1] = new LoaderReverseAction(_wrapper, _injector, Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActions[2]);
	_firingActions[0] = new LoaderForwardAction(_wrapper, Context::GetConfiguration(), Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActions[1]);
	
	_firingActionsForcedMixing[2] = new PrepareForFiringAction(_wrapper, _firingController, Context::GetActuators(), Context::GetSensors(), nullptr, _firingScreen);
	_firingActionsForcedMixing[1] = new LoaderReverseActionForcedMixing(_wrapper, Context::GetConfiguration(), _injector, Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActionsForcedMixing[2]);
	_firingActionsForcedMixing[0] = new LoaderForwardAction(_wrapper, Context::GetConfiguration(), Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActionsForcedMixing[1]);

	_firingSequencer = new FiringSequencer(_wrapper, _firingActions[0], _firingActionsForcedMixing[0], _firingScreen);
}

void MainSequence::InitializeHwTest()
{
	_checks = new IHwCheck*[HW_CHECKS_COUNT];

	_testScreen = new TestScreen(_wrapper);
	_testScreen->Refresh();

	_checks[0] = new BatteryCheck(_wrapper, _testScreen, Context::GetSensors());
	_checks[1] = new ButtonsCheck(_wrapper, _testScreen);
	_checks[2] = new LoaderCheck(_wrapper, _testScreen, Context::GetLoader());
	_checks[3] = new MachineryCheck(_wrapper, _testScreen, Context::GetActuators());
	_checks[4] = new SensorsCheck(_wrapper, _testScreen, Context::GetLoader(), Context::GetActuators(), Context::GetSensors());

	_hwChecksSequence = new HwCheckSequence(_wrapper, _checks, HW_CHECKS_COUNT);
}

void MainSequence::InitializeInjectorTest()
{
	_injector = new Injector(Context::GetConfiguration(), _wrapper, Context::GetSensors());
	_injectorTestScreen = new InjectorTestScreen(_wrapper, Context::GetSensors(), _injector);
	_injectorTestScreen->Refresh();
}

void MainSequence::InitializeConfigEdit()
{	
	_configScreen = new ConfigurationScreen(_wrapper, Context::GetConfiguration());
}

void MainSequence::InitializeMainMenu()
{
	_mainScreen = new MainScreen(_wrapper);
	_mainScreen->Draw();	
	_mainScreen->UpdateFiringMode();
}

void MainSequence::SwitchMode(OperationMode mode)
{
	auto current = Context::GetOperationMode();

	if(current == mode)
	{
		return;
	}

	_wrapper->ClearScreen();

	switch (current)
	{
	case ConfigEditScreen:
		{
			CleanupConfigEdit();
		}
		break;
	case FiringMode:
	case FiringModeForcedMixing:
		{
			CleanupFiringSequences();
		}
		break;
	case TestMode:
		{
			CleanupHwChecks();
		}
		break;
	case MainMenu:
		{
			CleanupMainMenu();
		}
		break;
	case InjectorTestMode:
		{
			CleanupInjectorTest();
		}
	break;
	default: ;
	}	

	switch(mode)
	{
	case ConfigEditScreen:
		{
			InitializeConfigEdit();
		}
		break;
	case FiringMode:
	case FiringModeForcedMixing:
		{
			InitializeFiringSequence();
		}
		break;
	case TestMode:
		{
			InitializeHwTest();
		}
		break;
	case InjectorTestMode:
		{
			InitializeInjectorTest();
		}
	break;
	case MainMenu:
		{
			InitializeMainMenu();
		}
	default: ;
	}

	_readyToSwitch = false;
	Context::SetOperationMode(mode);
}

void MainSequence::CleanupFiringSequences()
{
	if(_firingSequencer != nullptr)
	{
		delete _firingSequencer;
		_firingSequencer = nullptr;
	}

	if(_firingScreen != nullptr)
	{
		delete _firingScreen;
		_firingScreen = nullptr;
	}

	if(_firingActionsForcedMixing != nullptr)
	{
		for (auto i = 0; i < FIRING_ACTIONS_COUNT; i++)
		{
			delete _firingActionsForcedMixing[i];
		}
		delete _firingActionsForcedMixing;
		_firingActionsForcedMixing = nullptr;
	}

	if (_firingActions != nullptr)
	{
		for (auto i = 0; i < FIRING_ACTIONS_COUNT; i++)
		{
			delete _firingActions[i];
		}
		delete _firingActions;
		_firingActions = nullptr;
	}

	if(_injector != nullptr)
	{
		delete _injector;
		_injector = nullptr;
	}

	if(_firingController != nullptr)
	{
		delete _firingController;
		_firingController = nullptr;
	}
}

void MainSequence::CleanupHwChecks()
{
	if(_checks != nullptr)
	{
		for (auto i = 0; i < HW_CHECKS_COUNT; i++)
		{
			delete _checks[i];
		}
		delete _checks;
		_checks = nullptr;
	}

	if(_testScreen != nullptr)
	{
		delete _testScreen;
		_testScreen = nullptr;
	}

	if(_hwChecksSequence != nullptr)
	{
		delete _hwChecksSequence;
		_hwChecksSequence = nullptr;
	}
}

void MainSequence::CleanupInjectorTest()
{
	if(_injector != nullptr)
	{
		delete _injector;
		_injector = nullptr;
	}

	if(_injectorTestScreen != nullptr)
	{
		delete _injectorTestScreen;
		_injectorTestScreen = nullptr;
	}
}

void MainSequence::CleanupConfigEdit()
{		
	if(_configScreen != nullptr)
	{
		delete _configScreen;
		_configScreen = nullptr;
	}
}

void MainSequence::CleanupMainMenu() 
{
	if (_mainScreen != nullptr)
	{
		delete _mainScreen;
		_mainScreen = nullptr;
	}
}

SystemState MainSequence::RunHwChecks()
{
	if (_hwChecksSequence != nullptr)
	{
		if(_waitingForInput)
		{
			if (Context::GetButtonsController().IsButtonPressed(x1A)) //continue
			{
				_waitingForInput = false;
				_hwChecksSequence->Skip();
			}
			else
			{
				return SystemIdle;
			}			
		}

		auto result = _hwChecksSequence->Run();

		switch (result)
		{
		case Failed:
			{
				_waitingForInput = true;
				return SystemIdle;
			}
		case Passed:
			{
				if(Context::GetButtonsController().IsButtonPressed(x2B)) //stop
				{
					SwitchMode(MainMenu);
					return SystemIdle;
				}		

				return SystemRunning;
			}
		case Interrupted:
			{
				SwitchMode(MainMenu);
				return SystemIdle;
			}
		case Running:
			{
				return SystemRunning;
			}		
		}
	}

	return SystemIdle;
}

SystemState MainSequence::RunInjectorTest()
{
	if (_injectorTestScreen != nullptr)
	{
		if (Context::GetButtonsController().IsButtonPressed(x2B)) //stop
		{
			SwitchMode(MainMenu);
			return SystemIdle;
		}

		_injectorTestScreen->Draw();

		return SystemRunning;	
	}

	return SystemIdle;
}

SystemState MainSequence::RunFiringSequence()
{
	if(_firingSequencer != nullptr)
	{
		if(Context::GetButtonsController().IsButtonPressed(x4D)) //stop
		{
			_firingSequencer->Stop();
			SwitchMode(MainMenu);
			return SystemIdle;
		}

		auto result = _firingSequencer->Execute();

		switch (result)
		{
		case Error:
			{
				if(Context::GetButtonsController().IsButtonPressed(x1A)) //continue
				{
					return _firingSequencer->Continue() ? SystemRunning : SystemError;
				}

				return SystemError;
			}
		case Executing:
		case Waiting:
			{
				return SystemRunning;
			}
		case Completed:
			{
				return SystemIdle;
			}
		}
	}

	return SystemIdle;
}

SystemState MainSequence::RunConfigEdit() const
{
	if(_configScreen == nullptr)
	{
		return SystemError;
	}

	_configScreen->Draw();

	return SystemIdle;
}

SystemState MainSequence::RunMainMenu()
{
	if(_mainScreen == nullptr)
	{			
		return SystemError;
	}
	
	auto controller = Context::GetButtonsController();	
	
	if (!_readyToSwitch)
	{
		if (controller.IsButtonPressed(x1A) || 
			controller.IsButtonPressed(x2B) || 
			controller.IsButtonPressed(x3C) || 
			controller.IsButtonPressed(x4D) || 
			controller.IsButtonPressed(x5E) || 
			controller.IsButtonPressed(x6F) ||
			controller.AreButtonsPressed(x2B, x3C))
		{
			_wrapper->Delay(1000);
			return SystemIdle;
		}

		_readyToSwitch = true;
	}

	if(controller.AreButtonsPressed(x2B, x3C))
	{
		SwitchMode(InjectorTestMode);
		return SystemRunning;
	}

	if (controller.IsButtonPressed(x1A))
	{
		SwitchMode(FiringMode);
		return SystemRunning;
	}

	if (controller.IsButtonPressed(x2B))
	{
		SwitchMode(FiringModeForcedMixing);
		return SystemRunning;
	}

	if (controller.IsButtonPressed(x3C))
	{
		SwitchMode(ConfigEditScreen);
		return SystemRunning;
	}

	if (controller.IsButtonPressed(x4D))
	{
		SwitchMode(TestMode);
		return SystemRunning;
	}

	if (controller.IsButtonPressed(x5E))
	{
		Context::SetFiringSequenceMode(Auto);
		_mainScreen->UpdateFiringMode();
		return SystemIdle;
	}

	if (controller.IsButtonPressed(x6F))
	{
		Context::SetFiringSequenceMode(SemiAuto);
		_mainScreen->UpdateFiringMode();
		return SystemIdle;
	}	

	return SystemIdle;
}

