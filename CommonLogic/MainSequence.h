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
#include "ManualScreen.h"

#define FIRING_ACTIONS_COUNT 3
#define SWITCH_DELAY 1000

class MainSequence
{
public:
	MainSequence(IArduinoWrapper* wrapper);	

	~MainSequence();
	
	SystemState Run();

	void Init();
private:
	void InitializeFiringSequence();
	void InitializeHwTest();
	void InitializeInjectorTest();
	void InitializeConfigEdit();
	void InitializeMainMenu();
	void InitializeManualMode();

	void SwitchMode(OperationMode mode);

	void CleanupFiringSequences();
	void CleanupHwChecks();
	void CleanupInjectorTest();
	void CleanupConfigEdit();
	void CleanupMainMenu();	
	void CleanupManualMode();

	bool IsSwitchDelay();

	SystemState RunHwChecks();
	SystemState RunInjectorTest();
	SystemState RunFiringSequence();
	SystemState RunConfigEdit() const;
	SystemState RunMainMenu();

	IArduinoWrapper* _wrapper;

	IHwCheck** _checks;
	TestScreen* _testScreen;
	HwCheckSequence* _hwChecksSequence;
	bool _waitingForInput;
	bool _readyToSwitch;	

	long _switchDelayStart;
	bool _switchDelay;

	FiringScreen* _firingScreen;
	FiringSequencer* _firingSequencer;
	FiringController* _firingController;
	IAction** _firingActions;
	IAction** _firingActionsForcedMixing;
	Injector* _injector;

	IAction* _manualAction;

	MainScreen* _mainScreen;
	ConfigurationScreen* _configScreen;	
	InjectorTestScreen* _injectorTestScreen;
	ManualScreen* _manualScreen;	
};

