#include "HwCheckSequence.h"
#include "Context.h"


HwCheckSequence::HwCheckSequence(IArduinoWrapper * wrapper, IHwCheck ** checks, int checksCount) : _wrapper(wrapper)
{
	_checks = checks;
	_checksCount = checksCount;
	_checkIndex = 0;
}

HwCheckSequence::~HwCheckSequence()
{
}

CheckResult HwCheckSequence::Run()
{
	if (Context::GetButtonsController().AreButtonsPressed(x1A, x3C))
	{
		return Interrupted;
	}

	auto check = _checks[_checkIndex];
	auto checkResult = check->Check();

	switch (checkResult)
	{
	case Interrupted:
	{
		_checkIndex = 0;
		return Interrupted;
	}
	case Failed:
	{
		_checkIndex = 0;
		return Failed;
	}
	case Running:
	{
		return Running;
	}	
	case Passed:
	{
		_checkIndex++;
		if (_checkIndex >= _checksCount)
		{
			_checkIndex = 0;			
		}		

		return Passed;
	}	
	default:
	{
		Context::LogMessage("Unexpected hw check result code");
		_checkIndex = 0;
		return Failed;
	}
	}	
}

void HwCheckSequence::Skip()
{
	_checkIndex++;

	if(_checkIndex >= HW_CHECKS_COUNT - 1)
	{
		_checkIndex = 0;
	}
}
