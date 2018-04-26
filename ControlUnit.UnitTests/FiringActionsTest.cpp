#include "stdafx.h"
#include "CppUnitTest.h"
#include "ButtonsController.h"
#include "Context.h"
#include "MainSequence.h"
#include <thread>
#include "ArduinoFrameStub.h"
#include "LoaderForwardActionTest_Frame.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	TEST_CLASS(FiringActionsTest)
	{
	public:

		TEST_METHOD(LoaderForwardActionTest)
		{
			auto frameFactory = LoaderForwardActionTest_Frame(100);
			auto frame = frameFactory.GetTestFrame();
			
			auto wrapper = ArduinoFrameStub(frame);
			//auto storage = ConfigurationValueStorage(&wrapper);
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			auto sensors = Sensors(&wrapper);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators, &sensors, frame->GetConfiguration());

			auto mainSequence = MainSequence(&wrapper);

			for (auto i = 0; i < 6000; i++)
			{
				auto systemState = mainSequence.Run();
				context.SetState(systemState);
				wrapper.Delay(100);
				frame->IncrementFrame();
			}
		}

		TEST_METHOD(LoaderReverseActionTest)
		{
			
			
		}	
	};
}