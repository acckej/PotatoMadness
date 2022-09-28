#include "ButtonsCheck.h"
#include "Context.h"

ButtonsCheck::ButtonsCheck(IArduinoWrapper* wrapper, TestScreen* screen): IHwCheck(wrapper, screen, nullptr)
{
}

CheckResult ButtonsCheck::Check()
{
	if(IsIdleCycle(CYCLE_DURATION))
	{
		return Running;
	}

	if (_cyclesCounter == 0)
	{
		_screen->Println("Buttons test", 1);
		_screen->Println("A+B-intrpt, A+D-end", 4);
	}

	auto controller = Context::GetButtonsController();

	if (controller.AreButtonsPressed(x1A, x2B))
	{
		_screen->Println("Interrupted", 3);
		return Interrupted;
	}

	if (controller.AreButtonsPressed(x1A, x4D))
	{
		_screen->Println("Passed", 3);
		return Passed;
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
	case x1A:
		_screen->Println("x1", 2);
		break;
	case x2B:
		_screen->Println("x2", 2);
		break;
	case x3C:
		_screen->Println("x3", 2);
		break;
	case x4D:
		_screen->Println("x4", 2);
		break;
	case x5E:
		_screen->Println("x5", 2);
		break;
	case x6F:
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

	_cyclesCounter++;
	
	return Running;
}
