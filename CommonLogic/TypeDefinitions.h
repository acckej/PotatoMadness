#pragma once

#define ARDUINO_LOW 0
#define ARDUINO_HIGH 1

enum ActionState
{
	Completed,
	Error,
	Waiting,
	Executing
};

enum ErrorCodes
{
	NoError = 0,

	ReceiverPressureLow = 1,
	ReceiverPressureHigh = 2,

	LowVoltage = 3,

	LoaderOverload = 4,
	LoaderForwardTimeout = 5,
	IncorrectLoaderPositionRev = 6,
	IncorrectLoaderPositionFwd = 7,
	LoaderReverseTimeout = 8,

	NoAmmo = 9,
	FssWithoutBlast = 10,
	RssWithoutFront = 11,
	RssWithoutBlast = 12,
	FssEqualsRss = 13,
	IncorrectShotSensorsState = 14,

	FiringTimeout = 15,

	IncorrectInjectionTime = 16,

	Unspecified = 1000
};

inline bool IsRecoverableError(ErrorCodes code)
{
	return code == NoAmmo || code == LoaderOverload || code == NoError;
}

#ifdef WIN32

typedef float ArduinoDouble;

#else

typedef double ArduinoDouble;

#endif




