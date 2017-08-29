#include "ButtonsCheck.h"
#include "Context.h"

ButtonsCheck::ButtonsCheck(IArduinoWrapper* wrapper, TestScreen* screen): IHwCheck(wrapper, screen)
{
}

CheckResult ButtonsCheck::Check()
{
	_screen->Println("Buttons test", 1);

	auto controller = Context::GetButtonsController();

	if (controller.AreButtonsPressed(x1, x2))
	{
		return Interrupted;
	}

	auto btn = controller.GetPressedButton();

#ifdef Debug
	Context::LogMessage("Check buttons");
#endif

	switch (btn)
	{
	case Combo:
		_screen->Println("Combo", 2);
		break;
	case x1:
		_screen->Println("x1", 2);
		break;
	case x2:
		_screen->Println("x2", 2);
		break;
	case x3:
		_screen->Println("x3", 2);
		break;
	case x4:
		_screen->Println("x4", 2);
		break;
	case x5:
		_screen->Println("x5", 2);
		break;
	case x6:
		_screen->Println("x6", 2);
		break;
	case None:
		break;
	default:
	{
		_screen->Println("Error", 2);
		return Failed;
	}
	}

	_wrapper->Delay(100);

	return Running;
}
