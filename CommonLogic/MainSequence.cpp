#include "MainSequence.h"



MainSequence::MainSequence(IArduinoWrapper* wrapper)
{
}

SystemState MainSequence::Run()
{
	return SystemRunning;
}

void MainSequence::InitializeFiringSequence()
{
}

void MainSequence::InitializeHwTest()
{
}

void MainSequence::InitializeAfrEdit()
{
}

void MainSequence::SwitchMode(OperationMode mode)
{
}

