#pragma once
#include "IArduinoWrapper.h"
#include "Constants.h"
#include "IHwCheck.h"
#include "HwCheckSequence.h"
#include "FiringSequencer.h"
#include "Injector.h"


class MainSequence
{
public:
	MainSequence(IArduinoWrapper* wrapper);	
	
	SystemState Run();
private:
	void InitializeFiringSequence();

	void InitializeHwTest();

	void InitializeAfrEdit();

	void SwitchMode(OperationMode mode);

	IHwCheck** _checks;
	TestScreen* _testScreen;
	HwCheckSequence* _hwChecksSequence;

	FiringScreen* _firingScreen;
	FiringSequencer* _firingSequencer;
	IAction** _firingActions;
	Injector* _injector;
};

