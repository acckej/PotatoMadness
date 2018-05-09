#include "stdafx.h"
#include "CppUnitTest.h"
#include "ButtonsController.h"
#include "Context.h"
#include "MainSequence.h"
#include <thread>
#include "ArduinoFrameStub.h"
#include "HwChecksTest_Frame.h"
#include "HwChecksHoldButtons_Frame.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	TEST_CLASS(HwChecksFrameTest)
	{
	public:

		TEST_METHOD(HwChecksSequenceTest)
		{
			auto frameFactory = HwChecksTest_Frame(100);
			auto frame = frameFactory.GetTestFrame();

			auto wrapper = ArduinoFrameStub(frame);
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			auto sensors = Sensors(&wrapper);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators, &sensors, frame->GetConfiguration());

			auto mainSequence = MainSequence(&wrapper);

			for (auto i = 0; i < 300; i++)
			{
				auto systemState = mainSequence.Run();
				context.SetState(systemState);
				wrapper.Delay(100);
				frame->IncrementFrame();
			}
		}	
		
		TEST_METHOD(HwChecksHoldButtonsTest)
		{
			auto frameFactory = HwChecksHoldButtons_Frame(100);
			auto frame = frameFactory.GetTestFrame();

			auto wrapper = ArduinoFrameStub(frame);
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			auto sensors = Sensors(&wrapper);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators, &sensors, frame->GetConfiguration());

			auto mainSequence = MainSequence(&wrapper);

			for (auto i = 0; i < 50; i++)
			{
				auto systemState = mainSequence.Run();
				context.SetState(systemState);
				wrapper.Delay(100);
				frame->IncrementFrame();
			}
		}
	};
}