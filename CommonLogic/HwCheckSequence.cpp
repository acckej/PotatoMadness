#include "HwCheckSequence.h"
#include "Context.h"


HwCheckSequence::HwCheckSequence(IArduinoWrapper * wrapper, IHwCheck * checks, int checksCount)
{
	_wrapper = wrapper;
	_checks = checks;
	_checksCount = checksCount;
}

HwCheckSequence::~HwCheckSequence()
{
}

CheckResult HwCheckSequence::Run() const
{
	CheckResult result = Passed;

	for (auto i = 0; i < _checksCount; i++)
	{
		if(Context::GetButtonsController().AreButtonsPressed(x1, x3))
		{
			return Interrupted;
		}

		auto check = _checks[i];
		auto checkResult = check.Check();

		if(checkResult == Interrupted)
		{
			return Interrupted;
		}

		if(checkResult == Failed)
		{
			result = Failed;
		}
	}

	return result;
}
