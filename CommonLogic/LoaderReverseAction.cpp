#include "LoaderReverseAction.h"



LoaderReverseAction::LoaderReverseAction(IArduinoWrapper* wrapper): IAction(wrapper)
{
}

void LoaderReverseAction::Reset()
{
}

bool LoaderReverseAction::CheckPreconditions()
{
	return false;
}

void LoaderReverseAction::StartAction()
{
}

bool LoaderReverseAction::Execute()
{
	return false;
}

bool LoaderReverseAction::CheckPostConditions()
{
	return false;
}

void LoaderReverseAction::EndAction()
{
}

int LoaderReverseAction::GetActionDuration()
{
	return 0;
}
