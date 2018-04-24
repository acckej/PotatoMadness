﻿#include <iarduino_DHT.h>
#include "HwCheckSequence.h"
#include "ArduinoWrapper.h"
#include "Context.h"
#include "Actuators.h"
#include "SensorsCheck.h"
#include "Sensors.h"
#include "MainSequence.h"
#include "ConfigurationValueStorage.h"

//#include "MachineryCheck.h"
//#include "LoaderCheck.h"
//#include "ButtonsCheck.h"

#define Arduino

auto _wrapper = ArduinoWrapper();

auto _sensors = Sensors(&_wrapper);
auto config = ConfigurationValueStorage(&_wrapper);
auto _loader = Loader(&_wrapper);
auto _actuators = Actuators(&_wrapper);
auto _buttons = ButtonsController(&_wrapper, nullptr, 0);
auto _context = Context(&_wrapper, &_buttons, &_loader, &_actuators, &_sensors, &config);

auto screen = TestScreen(&_wrapper);
IHwCheck* checks[1];
auto bc = SensorsCheck(&_wrapper, &screen, &_loader, &_actuators, &_sensors);
auto seq = HwCheckSequence(&_wrapper, checks, 1);
CheckResult _hwCheckResult = Running;
bool _high = false;

void setup() 
{	
#ifdef Debug
	Serial.begin(9600);
#endif

	_wrapper.Init();
	checks[0] = &bc;

	pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{	
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
	
	if (_hwCheckResult == Running)
	{
		_hwCheckResult = seq.Run();
	}	
	else
	{
		delay(1000);
	}

	//Serial.println(_hwCheckResult);
}

