#include "stdafx.h"
#include "CppUnitTest.h"
#include "ArduinoStub.h"
#include "ButtonsController.h"
#include "Context.h"
#include "MainSequence.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	TEST_CLASS(FiringActionsTest)
	{
	public:

		TEST_METHOD(LoaderForwardActionTest)
		{
			auto wrapper = ArduinoStub(DigitalReadButtons, nullptr);			
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			auto sensors = Sensors(&wrapper);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators, &sensors);

			auto mainSequence = MainSequence(&wrapper);

			for (auto i = 0; i < 1000; i++)
			{
				mainSequence.Run();
			}
		}

		TEST_METHOD(LoaderReverseActionTest)
		{
			auto wrapper = ArduinoStub(DigitalReadLoader, DigitalWriteLoader, AnalogReadLoader);			
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			
		}

	private:
		static int DigitalReadButtons(int port)
		{
			return  ARDUINO_LOW;
		}

		static void DigitalWriteLoader(int port, int value)
		{
		}

		static int DigitalReadLoader(int port)
		{
			return ARDUINO_LOW;
		}

		static int AnalogReadLoader(int port)
		{
			return 0;
		}
	};
}