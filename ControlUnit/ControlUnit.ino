#include "HwCheckSequence.h"
#include "ArduinoWrapper.h"
#include "Context.h"
#include "ButtonsCheck.h"

#define Debug

auto _wrapper = ArduinoWrapper();
auto _buttons = ButtonsController(&_wrapper, nullptr, 0);
auto _context = Context(&_wrapper, &_buttons);

auto screen = TestScreen(&_wrapper);
IHwCheck* checks[1];
auto bc = ButtonsCheck(&_wrapper, &screen);
auto seq = HwCheckSequence(&_wrapper, checks, 1);
CheckResult _hwCheckResult = Running;

void setup() 
{	
	checks[0] = &bc;

#ifdef Debug
	Serial.begin(9600);
#endif
}

void loop() 
{
	if (_hwCheckResult == Running)
	{
		_hwCheckResult = seq.Run();
	}
}

