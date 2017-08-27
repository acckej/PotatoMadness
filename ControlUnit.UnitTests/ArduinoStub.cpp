#include "stdafx.h"
#include "ArduinoStub.h"

int ArduinoStub::DigitalRead(int port)
{
	return 0;
}

void ArduinoStub::DigitalWrite(int port, int value)
{
}

int ArduinoStub::AnalogRead(int port)
{
	return 0;
}

void ArduinoStub::AnalogWrite(int port, int value)
{
}

void ArduinoStub::Delay(unsigned long delay)
{
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

void ArduinoStub::Print(float val, int)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage("Lcd number print:");
	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(std::to_string(val).c_str());
}

void ArduinoStub::SerialPrint(char * message)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(message);
}
