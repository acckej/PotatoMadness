#include "stdafx.h"
#include "CppUnitTest.h"
#include "ArduinoStub.h"
#include "ScrollableScreen.h"
#include "ConfigurationScreen.h"
#include "ConfigurationValueStorage.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	static bool _increaseValueTestGo;
	static bool _decreaseValueTestGo;
	static bool _scrollUp;

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
			auto context = Context(&wrapper, &buttons, nullptr, nullptr, nullptr, &storage);

			storage.Load();
			_increaseValueTestGo = false;

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
			auto context = Context(&wrapper, &buttons, nullptr, nullptr, nullptr, &storage);

			storage.Load();			

			for (auto i = 0; i < 200; i++)
			{
				confScreen.Draw();

				wrapper.Delay(100);
			}
		}

		TEST_METHOD(IncreaseValueTest)
		{
			auto wrapper = ArduinoStub(DigitalReadButtonsIncreaseValue, nullptr);
			auto screen = ScrollableScreen(&wrapper);
			auto storage = ConfigurationValueStorage(&wrapper);
			auto confScreen = ConfigurationScreen(&wrapper, &storage);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, nullptr, nullptr, nullptr, &storage);

			storage.Load();
			_increaseValueTestGo = false;
			confScreen.Draw();
			_increaseValueTestGo = true;

			for (auto i = 0; i < 100; i++)
			{
				confScreen.Draw();

				wrapper.Delay(100);
			}
		}

		TEST_METHOD(DecreaseValueTest)
		{
			auto wrapper = ArduinoStub(DigitalReadButtonsDecreaseValue, nullptr);
			auto screen = ScrollableScreen(&wrapper);
			auto storage = ConfigurationValueStorage(&wrapper);
			auto confScreen = ConfigurationScreen(&wrapper, &storage);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, nullptr, nullptr, nullptr, &storage);

			storage.Load();
			_decreaseValueTestGo = false;
			confScreen.Draw();
			_decreaseValueTestGo = true;

			for (auto i = 0; i < 100; i++)
			{
				confScreen.Draw();

				wrapper.Delay(100);
			}
		}

		TEST_METHOD(ScrollScreenUpDownTest)
		{
			auto wrapper = ArduinoStub(DigitalReadButtonsScrollUpDown, nullptr);
			auto screen = ScrollableScreen(&wrapper);
			auto storage = ConfigurationValueStorage(&wrapper);
			auto confScreen = ConfigurationScreen(&wrapper, &storage);
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons, nullptr, nullptr, nullptr, &storage);

			storage.Load();
			_scrollUp = false;

			for (auto i = 0; i < 400; i++)
			{
				confScreen.Draw();

				wrapper.Delay(100);
			}

			_scrollUp = true;

			for (auto i = 0; i < 400; i++)
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

		static int DigitalReadButtonsScrollUpDown(int port)
		{
			if (port == BTN3_PORT && !_scrollUp)
			{
				return ARDUINO_HIGH;
			}

			if (port == BTN2_PORT && _scrollUp)
			{
				return ARDUINO_HIGH;
			}

			return  ARDUINO_LOW;
		}

		static int DigitalReadButtonsIncreaseValue(int port)
		{
			if (port == BTN4_PORT)
			{
				return _increaseValueTestGo ? ARDUINO_HIGH : ARDUINO_LOW;
			}

			return  ARDUINO_LOW;
		}

		static int DigitalReadButtonsDecreaseValue(int port)
		{
			if (port == BTN1_PORT)
			{
				return _decreaseValueTestGo ? ARDUINO_HIGH : ARDUINO_LOW;
			}

			return  ARDUINO_LOW;
		}
	};
}