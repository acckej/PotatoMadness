#include "FiringController.h"
#include "Constants.h"
#include "Context.h"

bool FiringController::_fireFlag;
unsigned long FiringController::_startTime;
unsigned long FiringController::_endTime;
IArduinoWrapper * FiringController::_wrapper;
bool FiringController::_frontSensorEngaged;
bool FiringController::_rearSensorEngaged;
ErrorCodes FiringController::_errorCode;

volatile int FiringController::b;
volatile int FiringController::r;
volatile int FiringController::f;

FiringController::FiringController(IArduinoWrapper* wrapper)
{
	_wrapper = wrapper;
	Reset();

	f = 0;
	r = 0;
	b = 0;
}

bool FiringController::GetFireFlag() const
{
	return _fireFlag;
}

void FiringController::FrontSpeedsensorHandler()
{
	f++;

	/*if(!_fireFlag)
	{
		_errorCode = FssWithoutBlast;
		return;
	}

	_startTime = _wrapper->GetMilliseconds();
	_frontSensorEngaged = true;	*/
}

void FiringController::BlastSensorHandler()
{
	b++;

	/*_fireFlag = true;
	Context::SetState(IdleCycle);	*/
}


ErrorCodes FiringController::GetErrorCode()
{
	return _errorCode;
}

void FiringController::Reset()
{
	_fireFlag = false;
	_startTime = 0;
	_frontSensorEngaged = false;	
	_rearSensorEngaged = false;
	_errorCode = NoError;
	_startTime = 0;
}

