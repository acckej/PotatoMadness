#include "ButtonsCheck.h"
#include "Context.h"

ButtonsCheck::ButtonsCheck(IArduinoWrapper* wrapper, TestScreen* screen): IHwCheck(wrapper, screen)
{
}


ButtonsCheck::~ButtonsCheck()
{
}

CheckResult ButtonsCheck::Check()
{
	_screen->PutTestMessage("Buttons test", 1);

	auto controller = Context::GetButtonsController();

	while (!controller.AreButtonsPressed(x1, x2))
	{
		auto btn = controller.GetPressedButton();

		switch (btn)
		{
		case Combo:
			_screen->PutTestMessage("Combo", 2);
			break;
		case x1:
			_screen->PutTestMessage("x1", 2);
			break;
		case x2:
			_screen->PutTestMessage("x2", 2);
			break;
		case x3:
			_screen->PutTestMessage("x3", 2);
			break;
		case x4:
			_screen->PutTestMessage("x4", 2);
			break;
		case x5:
			_screen->PutTestMessage("x5", 2);
			break;
		case x6:
			_screen->PutTestMessage("x6", 2);
			break;
		case None:
			break;
		default:
			{
				_screen->PutTestMessage("Error", 2);
				return Failed;
			}
		}

		_wrapper->Delay(100);
	}

	return Passed;
}
