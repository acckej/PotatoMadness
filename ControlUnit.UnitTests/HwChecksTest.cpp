#include "stdafx.h"
#include "CppUnitTest.h"
#include "../CommonLogic/HwCheckSequence.h"
#include "ButtonsCheck.h"
#include "ArduinoStub.h"
#include "ButtonsController.h"
#include "Context.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ControlUnitUnitTests
{		
	TEST_CLASS(HardwareChecksTest)
	{
	public:
		
		TEST_METHOD(HwChecksSequenceTest_Buttons)
		{
			auto wrapper = ArduinoStub();
			auto screen = TestScreen(&wrapper);			
			IHwCheck* checks[1];
			auto bc = new ButtonsCheck(&wrapper, &screen);	
			checks[0] = bc;
			auto buttons = ButtonsController(&wrapper, nullptr, 0);
			auto context = Context(&wrapper, &buttons);

			auto seq = HwCheckSequence(&wrapper, checks, 1);

			seq.Run();	
			delete bc;
		}

	};
}