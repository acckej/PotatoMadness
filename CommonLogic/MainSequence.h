#pragma once
#include "IArduinoWrapper.h"
#include "Constants.h"
#include "IHwCheck.h"
#include "HwCheckSequence.h"
#include "FiringSequencer.h"
#include "Injector.h"
#include "FiringController.h"
#include "MainScreen.h"
#include "ConfigurationScreen.h"
#include "InjectorTestScreen.h"

#define FIRING_ACTIONS_COUNT 3

class MainSequence
{
public:
	MainSequence(IArduinoWrapper* wrapper);	

	~MainSequence();
	
	SystemState Run();
private:
	void InitializeFiringSequence();
	void InitializeHwTest();
	void InitializeInjectorTest();
	void InitializeConfigEdit();
	void InitializeMainMenu();

	void SwitchMode(OperationMode mode);

	void CleanupFiringSequences();
	void CleanupHwChecks();
	void CleanupInjectorTest() const;
	void CleanupConfigEdit() const;
	void CleanupMainMenu() const;

	SystemState RunHwChecks();
	SystemState RunInjectorTest();
	SystemState RunFiringSequence();
	SystemState RunConfigEdit() const;
	SystemState RunMainMenu();

	IArduinoWrapper* _wrapper;

	IHwCheck** _checks;
	TestScreen* _testScreen;
	HwCheckSequence* _hwChecksSequence;

	FiringScreen* _firingScreen;
	FiringSequencer* _firingSequencer;
	FiringController* _firingController;
	IAction** _firingActions;
	IAction** _firingActionsForcedMixing;
	Injector* _injector;

	MainScreen* _mainScreen;

	ConfigurationScreen* _configScreen;	

	InjectorTestScreen* _injectorTestScreen;
};

