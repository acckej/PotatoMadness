#include "FiringSequencer.h"
#include "Constants.h"
#include "Context.h"


FiringSequencer::FiringSequencer(IArduinoWrapper* wrapper, IAction* startActionNormal, IAction* startActionForcedMixing, FiringScreen* screen)
{
	_wrapper = wrapper;

	_startActionNormal = startActionNormal;
	_startActionForcedMixing = startActionForcedMixing;
	_currentAction = nullptr;
	_screen = screen;
}

void FiringSequencer::Execute()
{
	auto mode = Context::GetOperationMode();
	if(mode != FiringMode && mode != FiringModeForcedMixing)
	{
		return;
	}

	auto status = Context::GetState();

	if(status == SystemError || status == SystemIdle)
	{
		return;
	}

	if(_currentAction == nullptr || _currentAction->GetNextAction() == nullptr)
	{
		_currentAction = mode == FiringMode ? _startActionNormal : _startActionForcedMixing;

		if(!_currentAction->CheckPreconditions())
		{
			HandleError("Precond. fail");
			return;
		}
	}

	auto result = _currentAction->Execute();

	_screen->PrintStatus(0, _currentAction->GetActionName());
	_screen->PrintStatus(1, "Status:");
	_screen->PrintNumber(_currentAction->GetFiringState());

	if(result == Error)
	{
		HandleError("Exec. fail");
		return;
	}

	if(result == Completed)
	{
		if (!_currentAction->CheckPreconditions())
		{
			HandleError("Postcond. fail");
			return;
		}

		_currentAction = _currentAction->GetNextAction();

		if (_currentAction != nullptr && !_currentAction->CheckPreconditions())
		{
			HandleError("Precond. fail");				
		}
	}
}

void FiringSequencer::Stop() const
{
	if(_currentAction == nullptr)
	{
		return;
	}

	_currentAction->EndAction();

	Context::SetState(SystemIdle);
}

void FiringSequencer::Continue()
{
	auto mode = Context::GetOperationMode();
	if (mode != FiringMode && mode != FiringModeForcedMixing)
	{
		return;
	}

	if (_currentAction == nullptr)
	{
		return;
	}

	auto err = _currentAction->GetErrorCode();

	if(IsRecoverableError(err))
	{
		_currentAction->Reset();		
	}
	else
	{
		_currentAction = mode == FiringMode ? _startActionNormal : _startActionForcedMixing;
	}

	Context::SetState(SystemRunning);
}

void FiringSequencer::HandleError(const char * message) const
{
	auto code = _currentAction->GetErrorCode();
	_screen->PrintStatus(0, message);
	_screen->PrintStatus(1, "err. code:");
	_screen->PrintNumber(code);

	Context::SetState(SystemError);
}


