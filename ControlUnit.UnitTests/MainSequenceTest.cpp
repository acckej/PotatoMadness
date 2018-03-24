#include "stdafx.h"
#include "CppUnitTest.h"
#include "ArduinoStub.h"
#include "ButtonsController.h"
#include "Context.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	TEST_CLASS(MainSequenceTest)
	{
	public:

		TEST_METHOD(RunMainSequenceTest)
		{
			auto wrapper = ArduinoStub(DigitalReadButtons, nullptr);




		}

	private:
		static int DigitalReadButtons(int port)
		{
			return  ARDUINO_LOW;
		}
	};
}