//#include <iarduino_DHT.h>
#include "HwCheckSequence.h"
#include "ArduinoWrapper.h"
#include "Context.h"
#include "Actuators.h"

#include "SensorsCheck.h"
#include "MachineryCheck.h"
//#include "ButtonsCheck.h"
#include "LoaderCheck.h"
////#include "BatteryCheck.h"
//
//#include "BatteryCheck.h"
//#include "ButtonsCheck.h"
////#include "Sensors.h"
////#include "CalculationConstants.h"
#include "MainSequence.h"
#include "ConfigurationValueStorage.h"
#include "FireCheck.h"
//#include "SensorsCheck.h"
//#include "IgnitionCheck.h"
//#include "MachineryCheck.h"
//#include "SensorsCheck.h"
//
//#define Arduino
//
auto g_wrapper = ArduinoWrapper();
//
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
auto g_bc = SensorsCheck(&g_wrapper, &g_screen, &g_loader, &g_actuators, &g_sensors);///
//auto g_bc = MachineryCheck(&g_wrapper, &g_screen, &g_actuators);///
//auto g_bc = LoaderCheck(&g_wrapper, &g_screen, &g_loader);///
//auto bc = BatteryCheck(&wrapper, &screen, &sensors);///
//auto bc = ButtonsCheck(&wrapper, &screen);///
//auto bc = IgnitionCheck(& wrapper, & screen, &loader, &actuators);///
//auto g_bc = FireCheck(&g_wrapper, &g_screen, &g_loader, &g_actuators, &g_sensors, &g_buttons, &g_injector);

auto g_seq = HwCheckSequence(&g_wrapper, checks, 1);///
CheckResult hw_check_result = Running;///

void setup()
{
#ifdef Debug
	Serial.begin(SERIAL_SPEED);
#endif	

	g_wrapper.Init();

	checks[0] = &g_bc;//////

	pinMode(LED_BUILTIN, OUTPUT);

	Context::Halt();	

	//main_sequence.Init();

	g_config.Load();
	g_config.Save();
}


void loop()
{
	//if (Context::GetState() == SystemIdle)
	//{
	//	/*if (!Context::IncrementIdleCycleCounter())
	//	{
	//		return;
	//	}*/
	//	return;
	//}

	/*
	if (Context::GetState() != IdleCycle)
	{
		auto state = _mainSequence.Run();
		Context::SetState(state);
	}*/

	if (g_high)///
	{
		digitalWrite(13, HIGH);
		g_high = false;
	}
	else
	{
		digitalWrite(13, LOW);
		g_high = true;
	}

	//delay(200);///

	//Serial.println("_____");
	//Serial.println(g_injector.CalculateInjectionTime());
	//Serial.println(g_injector.GetInjectedPortion(), 7);
	//Serial.println(g_injector.GetGasFlow(), 10);
	////GetGasConcentration() * GetCorrectionCoefficient() * GetChamberAirMass()
	//Serial.println(g_injector.GetGasConcentration());
	//Serial.println(">>>>>>");

	//Serial.println(g_injector.GetGasDensity());
	//Serial.println(g_injector.GetGasFlowSpeed());
	//Serial.println(g_injector.GetValveArea(), 10);

	//Serial.println("++++++");
	//Serial.println(g_injector.GetChamberAirMass(), 10);
	//Serial.println(g_injector.GetDryAirMass(), 10);
	//
	//Serial.println(g_injector.GetCorrectionCoefficient());
	//Serial.println(g_config.GetChamberVolume());

	//Serial.println(g_injector.GetMoistAirDensity());

	//Serial.println(g_injector.GetChamberAirMass(), 10);

	//Serial.println("||||");
	//Serial.println(g_injector.GetDryAirPressure());
	//Serial.println(g_wrapper.GetAtmPressure());

	if (hw_check_result == Running)//
	{
		hw_check_result = g_seq.Run();///
	}	
}

