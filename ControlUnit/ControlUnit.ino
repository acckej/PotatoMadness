#include <iarduino_DHT.h>
#include "HwCheckSequence.h"
#include "ArduinoWrapper.h"
//#include "Context.h"
#include "Actuators.h"

//#include "SensorsCheck.h"
//#include "MachineryCheck.h"
//#include "ButtonsCheck.h"
#include "LoaderCheck.h"
//#include "BatteryCheck.h"

#include "BatteryCheck.h"
#include "ButtonsCheck.h"
//#include "Sensors.h"
#include "MainSequence.h"
#include "ConfigurationValueStorage.h"
#include "FireCheck.h"
#include "IgnitionCheck.h"
#include "MachineryCheck.h"
#include "SensorsCheck.h"

#define Arduino

auto g_wrapper = ArduinoWrapper();

auto g_sensors = Sensors(&g_wrapper);
auto g_config = ConfigurationValueStorage(&g_wrapper);
auto g_loader = Loader(&g_wrapper);
auto g_actuators = Actuators(&g_wrapper);
auto g_buttons = ButtonsController(&g_wrapper, nullptr, 0);
auto g_context = Context(&g_wrapper, &g_buttons, &g_loader, &g_actuators, &g_sensors, &g_config);
auto main_sequence = MainSequence(&g_wrapper);
auto g_injector = Injector(&g_config, &g_wrapper, &g_sensors);


bool g_high = false;///

auto g_screen = TestScreen(&g_wrapper);///
IHwCheck* checks[1];///
//auto bc = SensorsCheck(&wrapper, &screen, &loader, &actuators, &sensors);///
//auto bc = MachineryCheck(&wrapper, &screen, &actuators);///
//auto bc = LoaderCheck(&wrapper, &screen, &loader);///
//auto bc = BatteryCheck(&wrapper, &screen, &sensors);///
//auto bc = ButtonsCheck(&wrapper, &screen);///
//auto bc = IgnitionCheck(& wrapper, & screen, &loader, &actuators);///
auto g_bc = FireCheck(&g_wrapper, &g_screen, &g_loader, &g_actuators, &g_sensors, &g_buttons, &g_injector);

auto g_seq = HwCheckSequence(&g_wrapper, checks, 1);///
CheckResult hw_check_result = Running;///

void setup() 
{	
#ifdef Debug
	Serial.begin(9600);
#endif	

	g_wrapper.Init();

	checks[0] = &g_bc;//////

	pinMode(LED_BUILTIN, OUTPUT);

	g_context.Halt();

	//attachInterrupt(digitalPinToInterrupt(BLAST_SENSOR_PORT), FiringController::BlastSensorHandler, RISING);///
	//attachInterrupt(digitalPinToInterrupt(FSS_PORT), FiringController::FrontSpeedsensorHandler, RISING);///
	//attachInterrupt(digitalPinToInterrupt(RSS_PORT), FiringController::RearSpeedSensorHandler, RISING);///	

	//_mainSequence.Init();
}

void loop() 
{	
	/*if (_context.GetState() == SystemIdle)
	{
		if (!_context.IncrementIdleCycleCounter())
		{
			return;
		}
	}

	if (Context::GetState() != IdleCycle)
	{
		auto state = _mainSequence.Run();
		Context::SetState(state);
	}*/

	/*_wrapper.SetScreenCursor(0, 0);
	_wrapper.Print(i);
	i++;*/

	if(g_high)///
	{
		digitalWrite(13, HIGH);		
		g_high = false;
	}
	else
	{
		digitalWrite(13, LOW);		
		g_high = true;
	}	

	delay(200);///
	
	if (hw_check_result == Running)//
	{
		hw_check_result = g_seq.Run();///
	}
}

