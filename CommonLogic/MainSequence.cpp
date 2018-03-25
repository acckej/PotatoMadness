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

	SwitchMode(MainMenu);
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
	switch (Context::GetOperationMode())
	{
	case MainMenu:
		{
			return RunMainMenu();
		}
		break;
	case ConfigEditScreen:
		{
			return RunConfigEdit();
		}
		break;
	case FiringMode:
		FiringModeForcedMixing:
		{
			return RunFiringSequence();
		}
		break;
	case TestMode:
		{
		return RunHwChecks();
		}
		break;	
	default: ;
	}

	return SystemRunning;
}

void MainSequence::InitializeFiringSequence()
{
	_firingActions = new IAction*[3];
	_firingActionsForcedMixing = new IAction*[3];

	_firingController = new FiringController(_wrapper);
	_injector = new Injector(Context::GetConfiguration(), _wrapper);

	_firingActions[2] = new PrepareForFiringAction(_wrapper, _firingController, Context::GetActuators(), Context::GetSensors(), nullptr);
	_firingActions[1] = new LoaderReverseAction(_wrapper, _injector, Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActions[2]);
	_firingActions[0] = new LoaderForwardAction(_wrapper, Context::GetConfiguration(), Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActions[1]);

	_firingActionsForcedMixing[2] = new PrepareForFiringAction(_wrapper, _firingController, Context::GetActuators(), Context::GetSensors(), nullptr);
	_firingActionsForcedMixing[1] = new LoaderReverseActionForcedMixing(_wrapper, Context::GetConfiguration(), _injector, Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActionsForcedMixing[2]);
	_firingActionsForcedMixing[0] = new LoaderForwardAction(_wrapper, Context::GetConfiguration(), Context::GetLoader(), Context::GetActuators(), Context::GetSensors(), _firingActionsForcedMixing[1]);

	_firingScreen = new FiringScreen(_wrapper);
	
	_firingSequencer = new FiringSequencer(_wrapper, _firingActions[0], _firingActionsForcedMixing[0], _firingScreen);
}

void MainSequence::InitializeHwTest()
{
	_checks = new IHwCheck*[5];

	_testScreen = new TestScreen(_wrapper);

	_checks[0] = new BatteryCheck(_wrapper, _testScreen, Context::GetSensors());
	_checks[1] = new ButtonsCheck(_wrapper, _testScreen);
	_checks[2] = new LoaderCheck(_wrapper, _testScreen, Context::GetLoader());
	_checks[3] = new MachineryCheck(_wrapper, _testScreen, Context::GetActuators());
	_checks[4] = new SensorsCheck(_wrapper, _testScreen, Context::GetLoader(), Context::GetActuators(), Context::GetSensors());

	_hwChecksSequence = new HwCheckSequence(_wrapper, _checks, 5);
}

void MainSequence::InitializeConfigEdit()
{
}

void MainSequence::InitializeMainMenu()
{
	_mainScreen = new MainScreen(_wrapper);
}

void MainSequence::SwitchMode(OperationMode mode)
{
	auto current = Context::GetOperationMode();

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
	case MainMenu:
		{
			InitializeMainMenu();
		};
	default: ;
	}

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
		for (auto i = 0; i < 3; i++)
		{
			delete _firingActionsForcedMixing[i];
		}
		delete _firingActionsForcedMixing;
		_firingActionsForcedMixing = nullptr;
	}

	if (_firingActions != nullptr)
	{
		for (auto i = 0; i < 3; i++)
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
		for (auto i = 0; i < 5; i++)
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
}

void MainSequence::CleanupMainMenu()
{
	if (_mainScreen != nullptr)
	{
		delete _mainScreen;
	}
}

SystemState MainSequence::RunHwChecks()
{
	return SystemIdle;
}

SystemState MainSequence::RunFiringSequence()
{
	return SystemIdle;
}

SystemState MainSequence::RunConfigEdit()
{
	return SystemIdle;
}

SystemState MainSequence::RunMainMenu()
{
	return SystemIdle;
}

