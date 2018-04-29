#pragma once
#include "IArduinoWrapper.h"

class FiringController
{
public:
	FiringController(IArduinoWrapper* wrapper);

	bool GetFireFlag() const;

	static void FrontSpeedsensorHandler();

	static void RearSpeedSensorHandler();

	static void BlastSensorHandler();

	static float GetProjectileSpeed();

	static ErrorCodes GetErrorCode();

	static void Reset();
private:
	static bool _fireFlag;
	unsigned static long _startTime;
	unsigned static long _endTime;
	static IArduinoWrapper * _wrapper;
	static bool _frontSensorEngaged;	
	static ErrorCodes _errorCode;
	static bool _rearSensorEngaged;
};

