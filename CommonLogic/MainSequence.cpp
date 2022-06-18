#include "MainSequence.h"
#include "LoaderForwardAction.h"
#include "Context.h"
#include "PrepareForFiringAction.h"
#include "LoaderReverseAction.h"
#include "BatteryCheck.h"
#include "ButtonsCheck.h"
#include "LoaderCheck.h"
#include "MachineryCheck.h"
#include "SensorsCheck.h"
#include "ManualAction.h"


MainSequence::MainSequence(IArduinoWrapper* wrapper): _manualAction(nullptr), _manualScreen(nullptr)
{
	_wrapper = wrapper;

	_checks = nullptr;
	_firingActions = nullptr;	
	_firingController = nullptr;
	_firingScreen = nullptr;
	_firingSequencer = nullptr;
	_hwChecksSequence = nullptr;
	_injector = nullptr;
	_testScreen = nullptr;
	_mainScreen = nullptr;	
	_configScreen = nullptr;
	_waitingForInput = false;
	_readyToSwitch = false;
	_switchDelayStart = 0;
	_switchDelay = false;
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

	//TODO: manual mode
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
	
	_firingController = new FiringController(_wrapper);
	_injector = new Injector(Context::GetConfiguration(), _wrapper, Context::GetSensors());

	_firingScreen = new FiringScreen(_wrapper);
	_firingScreen->Refresh();

	_firingActions[2] = new PrepareForFiringAction(_wrapper, _firingController, Context::GetActuators(), Context::GetSensors(), nullptr, _firingScreen);
	_firingActions[1] = new LoaderReverseAction(_wrapper, _injector, Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActions[2]);
	_firingActions[0] = new LoaderForwardAction(_wrapper, Context::GetConfiguration(), Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActions[1]);
	

	_firingSequencer = new FiringSequencer(_wrapper, _firingActions[0],  _firingScreen);
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

void MainSequence::InitializeManualMode()
{
	_manualScreen = new ManualScreen(_wrapper);
	_manualScreen->Draw();

	_manualAction = new ManualAction(_wrapper, Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _manualScreen);
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
	case ManualMode:
		{
			CleanupManualMode();
		}
		break;	
	}	

	switch(mode)
	{
	case ConfigEditScreen:
		{
			InitializeConfigEdit();
		}
		break;
	case FiringMode:	
		{
			InitializeFiringSequence();
		}
		break;
	case TestMode:
		{
			InitializeHwTest();
		}
		break;	
	case ManualMode:
		{
			InitializeManualMode();
		}
		break;
	case MainMenu:
		{
			InitializeMainMenu();
		}
		break;	
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

void MainSequence::CleanupManualMode()
{
	if(_manualAction != nullptr)
	{
		delete _manualAction;
		_manualAction = nullptr;
	}

	if(_manualScreen != nullptr)
	{
		delete _manualScreen;
		_manualScreen = nullptr;
	}
}

bool MainSequence::IsSwitchDelay()
{
	if(_switchDelayStart == 0)
	{
		_switchDelayStart = _wrapper->GetMilliseconds();
		_switchDelay = true;
		return true;
	}

	if(_wrapper->GetMilliseconds() - _switchDelayStart > SWITCH_DELAY)
	{
		_switchDelayStart = 0;

		if (_switchDelay)
		{			
			_switchDelay = false;
			return false;
		}

		return true;
	}

	return true;
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

		const auto result = _hwChecksSequence->Run();

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

		const auto result = _firingSequencer->Execute();

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

	if (controller.IsButtonPressed(x1A))
	{
		SwitchMode(FiringMode);
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

	if (controller.IsButtonPressed(x3C))
	{
		if (IsSwitchDelay())
		{
			return SystemIdle;
		}

		SwitchMode(ConfigEditScreen);
		return SystemRunning;
	}

	if (controller.IsButtonPressed(x6F))
	{
		Context::SetFiringSequenceMode(SemiAuto);
		_mainScreen->UpdateFiringMode();
		return SystemIdle;
	}	

	return SystemIdle;
}

