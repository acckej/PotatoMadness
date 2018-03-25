#pragma once
#include "IArduinoWrapper.h"
#include "Constants.h"
#include "IHwCheck.h"
#include "HwCheckSequence.h"
#include "FiringSequencer.h"
#include "Injector.h"
#include "FiringController.h"
#include "MainScreen.h"


class MainSequence
{
public:
	MainSequence(IArduinoWrapper* wrapper);	

	~MainSequence();
	
	SystemState Run();
private:
	void InitializeFiringSequence();
	void InitializeHwTest();
	void InitializeConfigEdit();
	void InitializeMainMenu();

	void SwitchMode(OperationMode mode);

	void CleanupFiringSequences();
	void CleanupHwChecks();
	void CleanupConfigEdit();
	void CleanupMainMenu();

	SystemState RunHwChecks();
	SystemState RunFiringSequence();
	SystemState RunConfigEdit();
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
};

