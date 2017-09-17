#pragma once
#include "TypeDefinitions.h"
#include "IArduinoWrapper.h"

class IAction 
{
public:
	IAction(IArduinoWrapper* wrapper);			

	virtual void Reset();

	virtual bool CheckPreconditions();

	virtual void StartAction();	

	virtual ActionState Execute();

	virtual bool CheckPostConditions();

	virtual void EndAction();

	virtual int GetActionDuration();

	ErrorCodes GetErrorCode() const;

	bool IsError() const;

	IAction* GetNextAction() const;

	unsigned long GetStartTime();
protected:	
	IArduinoWrapper* _wrapper;
	ErrorCodes _errorCode;
	IAction* _nextAction;
	unsigned long _startTime;
};

