#include <iarduino_DHT.h>
#include "HwCheckSequence.h"
#include "ArduinoWrapper.h"
#include "Context.h"
#include "Actuators.h"
#include "SensorsCheck.h"
#include "Sensors.h"
#include "MainSequence.h"
#include "ConfigurationValueStorage.h"

#include "SensorsCheck.h"

#define Arduino

auto _wrapper = ArduinoWrapper();

auto _sensors = Sensors(&_wrapper);
auto _config = ConfigurationValueStorage(&_wrapper);
auto _loader = Loader(&_wrapper);
auto _actuators = Actuators(&_wrapper);
auto _buttons = ButtonsController(&_wrapper, nullptr, 0);
auto _context = Context(&_wrapper, &_buttons, &_loader, &_actuators, &_sensors, &_config);
auto _mainSequence = MainSequence(&_wrapper);

bool _high = false;

////
//auto screen = TestScreen(&_wrapper);
//IHwCheck* checks[1];
//auto bc = ButtonsCheck(&_wrapper, &screen);
//auto seq = HwCheckSequence(&_wrapper, checks, 1);
//CheckResult _hwCheckResult = Running;
////
auto screen = TestScreen(&_wrapper);
IHwCheck* checks[1];
auto bc = SensorsCheck(&_wrapper, &screen, &_loader, &_actuators, &_sensors);
auto seq = HwCheckSequence(&_wrapper, checks, 1);
CheckResult _hwCheckResult = Running;

void setup() 
{	
#ifdef Debug
	Serial.begin(9600);
#endif	

	_wrapper.Init();

	checks[0] = &bc;

	pinMode(LED_BUILTIN, OUTPUT);

	_context.Halt();
}

void loop() 
{	
	if (_context.GetState() == SystemIdle)
	{
		if (!_context.IncrementIdleCycleCounter())
		{
			return;
		}
	}

	if(_high)
	{
		digitalWrite(13, HIGH);
		_high = false;
	}
	else
	{
		digitalWrite(13, LOW);
		_high = true;
	}		

	/*screen.SetCursor(0, 0);
	screen.Print("test");

	delay(1000);	*/

	if (_hwCheckResult == Running)
	{
		_hwCheckResult = seq.Run();
	}
	else
	{
		delay(1000);
	}

	/*if (Context::GetState() != IdleCycle)
	{
		auto state = _mainSequence.Run();
		Context::SetState(state);
	}*/

	//Serial.println(_hwCheckResult);
}

