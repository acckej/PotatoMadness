#include "Sequenser.h"
#include "Constants.h"
#include "Context.h"


Sequenser::Sequenser(IArduinoWrapper* wrapper, IAction* startActionNormal, IAction* startActionForcedMixing)
{
	_wrapper = wrapper;

	_startActionNormal = startActionNormal;
	_startActionForcedMixing = startActionForcedMixing;
	_currentAction = nullptr;
}

void Sequenser::Execute()
{
	auto mode = Context::GetOperationMode();
	if(mode != FiringMode && mode != FiringModeForcedMixing)
	{
		return;
	}

	if(_currentAction->GetNextAction() == nullptr || _currentAction == nullptr)
	{
		_currentAction = mode == FiringMode ? _startActionNormal : _startActionForcedMixing;
	}


}


