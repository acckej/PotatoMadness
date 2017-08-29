#include "stdafx.h"
#include "CppUnitTest.h"
#include "../CommonLogic/HwCheckSequence.h"
#include "ButtonsCheck.h"
#include "ArduinoStub.h"
#include "ButtonsController.h"
#include "Context.h"
#include "LoaderCheck.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	static bool _stopButtonsTest;
	static int _buttonsPort;
	static int _currentValue;

	TEST_CLASS(HardwareChecksTest_ButtonsLoader)
	{
	public:
		
		TEST_METHOD(HwChecksSequenceTest_Buttons)
		{
			auto wrapper = ArduinoStub(DigitalReadButtons, nullptr);
			auto screen = TestScreen(&wrapper);			
			IHwCheck* checks[1];
			auto bc = new ButtonsCheck(&wrapper, &screen);	
			checks[0] = bc;
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons);

			_stopButtonsTest = false;			
			_buttonsPort = 0;

			auto seq = HwCheckSequence(&wrapper, checks, 1);

			for (auto i = 0; i < 10; i++)
			{
				seq.Run();

				_buttonsPort = BTN1_PORT;
				seq.Run();

				_buttonsPort = BTN2_PORT;
				seq.Run();

				_buttonsPort = BTN3_PORT;
				seq.Run();

				_buttonsPort = BTN4_PORT;
				seq.Run();

				_buttonsPort = BTN5_PORT;
				seq.Run();

				_buttonsPort = BTN6_PORT;
				seq.Run();				
			}

			_stopButtonsTest = true;

			seq.Run();
			seq.Run();

			delete bc;
		}

		TEST_METHOD(HwChecksSequenceTest_Loader)
		{
			auto wrapper = ArduinoStub(DigitalReadLoader, DigitalWriteLoader, AnalogReadLoader);
			auto screen = TestScreen(&wrapper);
			IHwCheck* checks[1];
			auto bc = new LoaderCheck(&wrapper, &screen);
			checks[0] = bc;
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons);

			_currentValue = 600;

			auto seq = HwCheckSequence(&wrapper, checks, 1);

			for (auto i = 0; i < 110; i++)
			{
				auto result = seq.Run();
			}			

			delete bc;
		}

	private:
		static int DigitalReadButtons(int port)
		{			
			if(port == _buttonsPort)
			{
				return ARDUINO_HIGH;
			}

			if(_stopButtonsTest && (port == BTN1_PORT || port == BTN2_PORT))
			{
				return ARDUINO_HIGH;
			}

			return  ARDUINO_LOW;
		}

		static void DigitalWriteLoader(int port, int value)
		{			
		}

		static int DigitalReadLoader(int port)
		{
			return 0;
		}

		static int AnalogReadLoader(int port)
		{
			if(port == LOADER_CURRENT_PORT)
			{
				return _currentValue;
			}

			return 0;
		}
	};
}