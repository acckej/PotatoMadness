#pragma once
#include "TypeDefinitions.h"
#include "IArduinoWrapper.h"
#include "Constants.h"

class IAction 
{
public:
	IAction(IArduinoWrapper* wrapper, IAction* nextAction);			

	virtual void Reset();	

	virtual const char* GetActionName();

	virtual bool CheckPreconditions();

	virtual void StartAction();	

	virtual ActionState Execute();

	virtual bool CheckPostConditions();

	virtual void EndAction();

	virtual int GetActionDuration();

	ErrorCodes GetErrorCode() const;	

	IAction* GetNextAction() const;

	unsigned long GetStartTime() const;

	FiringState GetFiringState() const;
protected:	
	IArduinoWrapper* _wrapper;
	ErrorCodes _errorCode;
	IAction* _nextAction;
	unsigned long _startTime;
	FiringState _firingState;
};

