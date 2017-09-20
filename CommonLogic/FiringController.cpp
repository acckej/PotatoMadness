#include "FiringController.h"
#include "Constants.h"

bool FiringController::_fireFlag;
unsigned long FiringController::_startTime;
unsigned long FiringController::_endTime;
IArduinoWrapper * FiringController::_wrapper;
bool FiringController::_frontSensorEngaged;
ErrorCodes FiringController::_errorCode;

FiringController::FiringController(IArduinoWrapper* wrapper)
{
	_wrapper = wrapper;
	Reset();
}

bool FiringController::GetFireFlag() const
{
	return _fireFlag;
}

void FiringController::FrontSpeedsensorHandler()
{
	if(!_fireFlag)
	{
		_errorCode = FssWithoutBlast;
		return;
	}

	_startTime = _wrapper->GetMilliseconds();
	_frontSensorEngaged = true;
}

void FiringController::RearSpeedSensorHandler()
{
	if(!_fireFlag)
	{
		_errorCode = RssWithoutBlast;
		return;
	}

	if(!_frontSensorEngaged)
	{
		_errorCode = RssWithoutFront;
		return;
	}

	_endTime = _wrapper->GetMilliseconds();
}

void FiringController::BlastSensorHandler()
{
	_fireFlag = true;
}

float FiringController::GetProjectileSpeed()
{
	if(_startTime == 0 || _endTime == 0 || _errorCode != NoError)
	{
		return 0;
	}

	auto diff = _endTime - _startTime;

	if(diff == 0)
	{
		_errorCode = FssEqualsRss;
		return 0;
	}

	auto result = SPEED_CONSTANT / (double(diff) / 1000);
	
	return result;
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
	_errorCode = NoError;
	_startTime = 0;
}

