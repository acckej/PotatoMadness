#include "stdafx.h"
#include "CppUnitTest.h"
#include "ButtonsController.h"
#include "Context.h"
#include "MainSequence.h"
#include <thread>
#include "ArduinoFrameStub.h"
#include "LoaderForwardActionTest_Frame.h"
#include "ConfigurationValueStorage.h"
#include "FiringActionForcedMixing_Frame.h"


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
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			auto sensors = Sensors(&wrapper);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators, &sensors, frame->GetConfiguration());

			auto mainSequence = MainSequence(&wrapper);

			for (auto i = 0; i < 70; i++)
			{
				auto systemState = mainSequence.Run();
				context.SetState(systemState);
				wrapper.Delay(100);
				frame->IncrementFrame();
			}
		}

		TEST_METHOD(LoaderReverseActionTest)
		{	
			auto frameFactory = LoaderForwardActionTest_Frame(100);
			auto frame = frameFactory.GetTestFrame();

			auto wrapper = ArduinoFrameStub(frame);
			auto storage = ConfigurationValueStorage(&wrapper);
			storage.Load();
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			auto sensors = Sensors(&wrapper);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators, &sensors, &storage);

			auto mainSequence = MainSequence(&wrapper);

			for (auto i = 0; i < 200; i++)
			{
				auto systemState = mainSequence.Run();
				context.SetState(systemState);
				wrapper.Delay(100);
				frame->IncrementFrame();
			}
		}	

		TEST_METHOD(FiringActionTest)
		{
			auto frameFactory = LoaderForwardActionTest_Frame(100);
			auto frame = frameFactory.GetTestFrame();

			auto wrapper = ArduinoFrameStub(frame);
			auto storage = ConfigurationValueStorage(&wrapper);
			storage.Load();
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			auto sensors = Sensors(&wrapper);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators, &sensors, &storage);

			auto mainSequence = MainSequence(&wrapper);

			for (auto i = 0; i < 300; i++)
			{
				auto systemState = mainSequence.Run();
				context.SetState(systemState);
				wrapper.Delay(100);
				frame->IncrementFrame();

				if(i == 90)
				{
					FiringController::BlastSensorHandler();
					frame->AddMilliseconds(5);
					FiringController::FrontSpeedsensorHandler();
					frame->AddMilliseconds(10);
					FiringController::RearSpeedSensorHandler();
				}				
			}
		}

		TEST_METHOD(FiringActionForcedMixingTest)
		{
			auto frameFactory = FiringActionForcedMixing_Frame(100);
			auto frame = frameFactory.GetTestFrame();

			auto wrapper = ArduinoFrameStub(frame);
			auto storage = ConfigurationValueStorage(&wrapper);
			storage.Load();
			auto loader = Loader(&wrapper);
			auto actuators = Actuators(&wrapper);
			auto sensors = Sensors(&wrapper);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, &loader, &actuators, &sensors, &storage);

			auto mainSequence = MainSequence(&wrapper);

			for (auto i = 0; i < 300; i++)
			{
				auto systemState = mainSequence.Run();
				context.SetState(systemState);
				wrapper.Delay(100);
				frame->IncrementFrame();

				if (i == 90)
				{
					FiringController::BlastSensorHandler();
					frame->AddMilliseconds(5);
					FiringController::FrontSpeedsensorHandler();
					frame->AddMilliseconds(10);
					FiringController::RearSpeedSensorHandler();
				}
			}
		}
	};
}