#include "stdafx.h"
#include "CppUnitTest.h"
#include "ArduinoStub.h"
#include "ButtonsController.h"
#include "Context.h"
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
			
			for(auto i = 0; i < SCREEN_ROWS; i++)
			{
				screen.Print("message");
				screen.PrintNumber(i);
			}
		}		

	private:
		static int DigitalReadButtons(int port)
		{
			return  ARDUINO_LOW;
		}		
	};
}