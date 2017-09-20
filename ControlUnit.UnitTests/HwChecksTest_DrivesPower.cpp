#include "stdafx.h"
#include "CppUnitTest.h"
#include "../CommonLogic/HwCheckSequence.h"
#include "ArduinoStub.h"
#include "ButtonsController.h"
#include "Context.h"
#include "BatteryCheck.h"
#include "IHwCheck.h"
#include "MachineryCheck.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	TEST_CLASS(HardwareChecksTest_DrivesPower)
	{
	public:

		TEST_METHOD(HwChecksSequenceTest_Power)
		{
			auto wrapper = ArduinoStub(nullptr, nullptr, AnalogReadLoader);
			auto screen = TestScreen(&wrapper);
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			IHwCheck* checks[1];
			auto bc = new BatteryCheck(&wrapper, &screen);
			checks[0] = bc;
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators);
			
			auto seq = HwCheckSequence(&wrapper, checks, 1);

			for (auto i = 0; i < 60; i++)
			{
				auto res = seq.Run();
				Assert::AreNotEqual(static_cast<int>(Failed), int(res));
			}

			delete bc;
		}	
		
		TEST_METHOD(HwChecksSequenceTest_Drives)
		{
			auto wrapper = ArduinoStub(nullptr, DigitalWriteDrives, nullptr);
			auto screen = TestScreen(&wrapper);
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);

			IHwCheck* checks[1];
			auto bc = new MachineryCheck(&wrapper, &screen, &actuators);
			checks[0] = bc;
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators);

			auto seq = HwCheckSequence(&wrapper, checks, 1);
			bool passed = false;

			for (auto i = 0; i < 210; i++)
			{
				auto res = seq.Run();
				Assert::AreNotEqual(static_cast<int>(Failed), int(res));
				if(res == Passed)
				{
					passed = true;
					break;
				}
			}

			Assert::IsTrue(passed);
			delete bc;
		}

	private:
		static int AnalogReadLoader(int port)
		{	
			if(port == VOLTAGE_PORT)
			{
				return 1000;
			}

			return 0;
		}

		static void DigitalWriteDrives(int port, int value)
		{			
		}
	};
}