#include "stdafx.h"
#include "ArduinoFrameStub.h"
#include <chrono>
#include <thread>


ArduinoFrameStub::ArduinoFrameStub(Frame* frame)
{
	_frame = frame;
}

void ArduinoFrameStub::Init()
{
}

int ArduinoFrameStub::DigitalRead(unsigned port)
{
	return _frame->DigitalRead(port);
}

void ArduinoFrameStub::DigitalWrite(unsigned port, int value)
{	
}

int ArduinoFrameStub::AnalogRead(unsigned port)
{
	return  _frame->AnalogRead(port);
}

void ArduinoFrameStub::AnalogWrite(unsigned port, int value)
{
}

void ArduinoFrameStub::Delay(unsigned long delay)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void ArduinoFrameStub::ClearScreen()
{
}

void ArduinoFrameStub::SetScreenCursor(char col, char row)
{
}

void ArduinoFrameStub::Print(const char[])
{
}

void ArduinoFrameStub::Print(double val, int digits)
{
}

void ArduinoFrameStub::PrintFormat(char* message, ...)
{
}

void ArduinoFrameStub::PrintFormatBuffer(char* buffer, char* message, ...)
{
}

void ArduinoFrameStub::LogFormat(char* message, ...)
{
}

void ArduinoFrameStub::LogFloatingPoint(double val)
{
}

void ArduinoFrameStub::SerialPrint(char* message)
{
}

float ArduinoFrameStub::GetAtmPressure()
{
	return _frame->GetAtmPressure();
}

float ArduinoFrameStub::GetInternalTemp()
{
	return _frame->GetInternalTemp();
}

float ArduinoFrameStub::GetExternalTemp()
{
	return _frame->GetExternalTemp();
}

float ArduinoFrameStub::GetExternalHumidity()
{
	return _frame->GetExternalHumidity();
}

unsigned long ArduinoFrameStub::GetMilliseconds()
{
	return _frame->GetMilliseconds();
}

void ArduinoFrameStub::IncrementFrame()
{
	_frame->IncrementFrame();
}



