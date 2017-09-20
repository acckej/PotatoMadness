#include "stdafx.h"
#include "CppUnitTest.h"
#include "../CommonLogic/HwCheckSequence.h"
#include "ArduinoStub.h"
#include "ButtonsController.h"
#include "Context.h"
#include "IHwCheck.h"
#include "SensorsCheck.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	TEST_CLASS(HardwareChecksTest_Sensor)
	{
	public:

		TEST_METHOD(HwChecksSequenceTest_Sensors)
		{
			auto wrapper = ArduinoStub(DigitalReadSensor, DigitalWriteSensor, AnalogReadSensor);
			auto screen = TestScreen(&wrapper);
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			IHwCheck* checks[1];
			auto bc = new SensorsCheck(&wrapper, &screen, &loader, &actuators);
			checks[0] = bc;
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators);

			auto seq = HwCheckSequence(&wrapper, checks, 1);

			for (auto i = 0; i < 200; i++)
			{
				auto res = seq.Run();
				Assert::AreNotEqual(static_cast<int>(Failed), int(res));
			}

			delete bc;
		}		

	private:
		static int AnalogReadSensor(int port)
		{			
			return 0;
		}

		static void DigitalWriteSensor(int port, int value)
		{
		}

		static int DigitalReadSensor(int port)
		{
			return 0;
		}
	};
}