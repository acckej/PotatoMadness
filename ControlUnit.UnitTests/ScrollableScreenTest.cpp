#include "stdafx.h"
#include "CppUnitTest.h"
#include "ArduinoStub.h"
#include "ScrollableScreen.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{
	TEST_CLASS(ScrollableScreenTest)
	{
	public:

		TEST_METHOD(ScrollScreenTest)
		{
			auto wrapper = ArduinoStub(DigitalReadButtons, nullptr);
			auto screen = ScrollableScreen(&wrapper);
			
			for(auto i = 0; i < ACTUAL_SCREEN_ROWS; i++)
			{
				screen.SetCursor(0, i);
				screen.Print("message");
				screen.PrintNumber(i);				
			}

			screen.Draw();

			//screen.Refresh();

			char buf[SCREEN_COLUMNS];

			for (auto i = 0; i < ACTUAL_SCREEN_ROWS; i++)
			{
				sprintf_s(buf, "Message%i", i);
				screen.Println(buf, i);
			}

			screen.Draw();
			
			for (auto i = 0; i < SCREEN_ROWS; i++)
			{
				screen.ScrollDown();
			}

			for (auto i = 0; i < SCREEN_ROWS; i++)
			{
				screen.ScrollUp();
			}
		}		

	private:
		static int DigitalReadButtons(int port)
		{
			return  ARDUINO_LOW;
		}		
	};
}