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
	NoError,

	ReceiverPressureLow,
	ReceiverPressureHigh,

	LowVoltage,

	LoaderOverload,
	LoaderForwardTimeout,
	IncorrectLoaderPositionRev,
	IncorrectLoaderPositionFwd,
	LoaderReverseTimeout,

	NoAmmo,
	FssWithoutBlast,
	RssWithoutFront,
	RssWithoutBlast,
	FssEqualsRss,
	IncorrectShotSensorsState,

	FiringTimeout,

	IncorrectInjectionTime,

	Unspecified
};




