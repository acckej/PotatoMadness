#include <iarduino_DHT.h>
#include "HwCheckSequence.h"
#include "ArduinoWrapper.h"
#include "Context.h"
#include "Actuators.h"
#include "SensorsCheck.h"
#include "Sensors.h"
#include "MainSequence.h"
#include "ConfigurationValueStorage.h"

#include "ButtonsCheck.h"

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
auto bc = ButtonsCheck(&_wrapper, &screen);
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

	attachInterrupt(digitalPinToInterrupt(BLAST_SENSOR_PORT), FiringController::BlastSensorHandler, HIGH);
	attachInterrupt(digitalPinToInterrupt(FSS_PORT), FiringController::FrontSpeedsensorHandler, HIGH);
	attachInterrupt(digitalPinToInterrupt(RSS_PORT), FiringController::RearSpeedSensorHandler, HIGH);
}

void loop() 
{	
	/*if (_context.GetState() == SystemIdle)
	{
		if (!_context.IncrementIdleCycleCounter())
		{
			return;
		}
	}*/

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
	
	_wrapper.SetScreenCursor(0, 0);
	_wrapper.Print(FiringController::b);
	_wrapper.SetScreenCursor(0, 1);
	_wrapper.Print(FiringController::f);
	_wrapper.SetScreenCursor(0, 2);
	_wrapper.Print(FiringController::r);

	if (_buttons.IsButtonPressed(x1A))
	{
		_sensors.ResetDebouncingTriggers();
		FiringController::b = 0;
		FiringController::f = 0;
		FiringController::r = 0;
	}

	if (_buttons.IsButtonPressed(x2B))
	{
		_loader.Forward();
	}

	if (_buttons.IsButtonPressed(x3C))
	{
		_loader.Reverse();
	}

	if (_buttons.IsButtonPressed(x4D))
	{
		_loader.Stop();
	}
	
	delay(200);

	/*if (_hwCheckResult == Running)
	{
		_hwCheckResult = seq.Run();
	}
	else
	{
		delay(1000);
	}*/

	/*if (Context::GetState() != IdleCycle)
	{
		auto state = _mainSequence.Run();
		Context::SetState(state);
	}*/

	//Serial.println(_hwCheckResult);
}

