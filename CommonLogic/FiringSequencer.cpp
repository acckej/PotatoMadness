#include "FiringSequencer.h"
#include "Constants.h"
#include "Context.h"


FiringSequencer::FiringSequencer(IArduinoWrapper* wrapper, IAction* startActionNormal, FiringScreen* screen)
{
	_wrapper = wrapper;

	_startActionNormal = startActionNormal;	
	_currentAction = nullptr;
	_screen = screen;
}

ActionState FiringSequencer::Execute()
{
	auto mode = Context::GetOperationMode();
	if(mode != FiringMode)
	{
		return Error;
	}

	auto status = Context::GetState();

	if(status == SystemError || status == SystemIdle)
	{
		return Error;
	}

	if(_currentAction == nullptr)
	{
		_currentAction = _startActionNormal;

		if(!_currentAction->CheckPreconditions())
		{
			HandleError("Precond. fail");
			return Error;
		}

		_currentAction->StartAction();
	}

	auto result = _currentAction->Execute();

	_screen->PrintStatus(0, _currentAction->GetActionName());
	_screen->PrintStatus(1, "Status:");
	_screen->PrintNumber(_currentAction->GetFiringState());

	if(result == Error)
	{
		HandleError("Exec. fail");
		return Error;
	}

	if(result == Completed)
	{
		_currentAction = _currentAction->GetNextAction();

		if (_currentAction != nullptr)
		{	
			if (!_currentAction->CheckPreconditions())
			{
				if (_currentAction->GetErrorCode() == NoAmmo)
				{
					_currentAction = nullptr;
					return Completed;
				}

				HandleError("Precond. fail");
				return Error;
			}
			
			_currentAction->StartAction();			
		}
	}

	return Executing;
}

void FiringSequencer::Stop() 
{
	if(_currentAction == nullptr)
	{
		return;
	}

	_currentAction->EndAction();
	_currentAction = nullptr;	
}

bool FiringSequencer::Continue()
{
	auto mode = Context::GetOperationMode();
	if (mode != FiringMode)
	{
		return false;
	}

	if (_currentAction == nullptr)
	{
		return false;
	}

	auto err = _currentAction->GetErrorCode();

	if(IsRecoverableError(err))
	{
		_currentAction->Reset();		
	}
	else
	{		
		_currentAction = nullptr;				
		return false;
	}	

	return true;
}

void FiringSequencer::HandleError(const char * message) const
{
	auto code = _currentAction->GetErrorCode();
	_screen->Refresh();
	_screen->PrintStatus(0, message);
	_screen->PrintStatus(1, "err. code:");
	_screen->PrintNumber(code);	

	Context::SetErrorCode(code);
}


