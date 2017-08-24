#pragma once
class IAction 
{
public:
	IAction();
	virtual ~IAction();

	virtual bool IsAsync();

	virtual bool IsCompleted();

	virtual void Reset();

	virtual bool CheckPreconditions();

	virtual void StartAction();

	virtual bool IsWaiting();

	virtual bool CheckRunningCondition();

	virtual bool CheckPostConditions();

	virtual void EndAction();
};

