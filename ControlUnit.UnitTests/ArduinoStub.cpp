#include "stdafx.h"
#include "ArduinoStub.h"
#include <thread>
#include <chrono>
#include <cstdarg>

ArduinoStub::ArduinoStub(DigitalReadDelegate digRead, DigitalWriteDelegate digWrite, AnalogReadDelegate anRead)
{
	_readDelegate = digRead;
	_writeDelegate = digWrite;
	_analogReadDelegate = anRead;
}

int ArduinoStub::DigitalRead(unsigned int port)
{
	return _readDelegate == nullptr ? 0 : _readDelegate(port);
}

void ArduinoStub::DigitalWrite(unsigned int port, int value)
{
	if (_writeDelegate != nullptr)
	{
		_writeDelegate(port, value);
	}
}

int ArduinoStub::AnalogRead(unsigned int port)
{
	return _analogReadDelegate == nullptr ? 0 : _analogReadDelegate(port);
}

void ArduinoStub::AnalogWrite(unsigned int port, int value)
{
}

void ArduinoStub::Delay(unsigned long delay)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(delay));
}

void ArduinoStub::ClearScreen()
{
}

void ArduinoStub::SetScreenCursor(char col, char row)
{
}

void ArduinoStub::Print(const char msg[])
{
	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("Lcd print:");
	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(msg);
}

void ArduinoStub::Print(double val, int)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("Lcd number print:");
	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(std::to_string(val).c_str());
}

void ArduinoStub::SerialPrint(char * message)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(message);
}

void ArduinoStub::PrintFormat(char * message, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, message);
	vsnprintf(buffer, 256, message, args);
	va_end(args);

	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(message);
}

float ArduinoStub::GetAtmPressure()
{
	return 0.0f;
}

float ArduinoStub::GetInternalTemp()
{
	return 0.0f;
}

float ArduinoStub::GetExternalTemp()
{
	return 0.0f;
}

float ArduinoStub::GetExternalHumidity()
{
	return 0.0f;
}

void ArduinoStub::PrintFormatBuffer(char* buffer, char* message, ...)
{	
	va_list args;
	va_start(args, message);
	vsnprintf(buffer, 256, message, args);
	va_end(args);
}

unsigned long ArduinoStub::GetMilliseconds()
{
	auto now = std::chrono::system_clock::now();

	return now.time_since_epoch().count() / 10000;
}

unsigned char ArduinoStub::ReadFromEeprom(short index)
{
	return _buffer[index];
}

void ArduinoStub::WriteToEeprom(short index, unsigned char value)
{
	_buffer[index] = value;
}

