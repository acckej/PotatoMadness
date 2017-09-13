#pragma once

#define ARDUINO_LOW 0
#define ARDUINO_HIGH 1

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

	IncorrectInjectionTime,

	Unspecified
};




