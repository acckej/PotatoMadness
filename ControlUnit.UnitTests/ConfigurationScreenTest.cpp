#include "stdafx.h"
#include "CppUnitTest.h"
#include "ArduinoStub.h"
#include "ScrollableScreen.h"
#include "ConfigurationScreen.h"
#include "ConfigurationValueStorage.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	TEST_CLASS(ConfigurationScreenTest)
	{
	public:

		TEST_METHOD(DrawScreenTest)
		{

			auto wrapper = ArduinoStub(DigitalReadButtons, nullptr);
			auto screen = ScrollableScreen(&wrapper);
			auto storage = ConfigurationValueStorage(&wrapper);
			auto confScreen = ConfigurationScreen(&wrapper, &storage);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, nullptr, nullptr, nullptr);

			storage.Load();

			for (auto i = 0; i < SCREEN_ROWS; i++)
			{
				confScreen.Draw();

				confScreen.ScrollDown();

				confScreen.Draw();
			}
		}

		TEST_METHOD(ScrollScreenDownTest)
		{
			auto wrapper = ArduinoStub(DigitalReadButtonsScrollDown, nullptr);
			auto screen = ScrollableScreen(&wrapper);
			auto storage = ConfigurationValueStorage(&wrapper);
			auto confScreen = ConfigurationScreen(&wrapper, &storage);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, nullptr, nullptr, nullptr);

			storage.Load();			

			for (auto i = 0; i < 200; i++)
			{
				confScreen.Draw();

				wrapper.Delay(100);
			}
		}

	private:
		static int DigitalReadButtons(int port)
		{
			return  ARDUINO_LOW;
		}

		static int DigitalReadButtonsScrollDown(int port)
		{
			if(port == BTN3_PORT)
			{
				return ARDUINO_HIGH;
			}

			return  ARDUINO_LOW;
		}
	};
}