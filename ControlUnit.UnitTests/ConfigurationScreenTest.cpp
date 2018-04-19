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
			}
		}

	private:
		static int DigitalReadButtons(int port)
		{
			return  ARDUINO_LOW;
		}
	};
}