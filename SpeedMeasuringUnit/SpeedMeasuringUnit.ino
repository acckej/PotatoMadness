#include <SoftwareSerial.h>
#include "Constants.h"
#include "Definitions.h"

SoftwareSerial g_link(SLAVE_SERIAL_RX, SLAVE_SERIAL_TX); // Rx, Tx

volatile bool g_interruptsEnabled = false;
volatile unsigned long g_start = 0;
volatile unsigned long g_time = 0;
volatile double g_speed = 0;


void setup()
{
	g_link.begin(SERIAL_SPEED);

	pinMode(MEAS_UNIT_LED_ONE, OUTPUT);
	pinMode(MEAS_UNIT_LED_TWO, OUTPUT);
	pinMode(FSS_PORT, INPUT_PULLUP);
	pinMode(RSS_PORT, INPUT_PULLUP);
	pinMode(SS_TRIGGER_RESET_PORT, OUTPUT);

	attachInterrupt(digitalPinToInterrupt(FSS_PORT), FssHandler, RISING);
	attachInterrupt(digitalPinToInterrupt(RSS_PORT), RssHandler, RISING);	
}

void loop()
{
	ReceiveCommand(); 

	/*if (!g_interruptsEnabled)
	{
		digitalWrite(MEAS_UNIT_LED_TWO, LOW);
		digitalWrite(MEAS_UNIT_LED_ONE, LOW);
		g_interruptsEnabled = true;
	}
	else
	{
		digitalWrite(MEAS_UNIT_LED_TWO, HIGH);
		digitalWrite(MEAS_UNIT_LED_ONE, HIGH);
		g_interruptsEnabled = false;
	}

	delay(1000);*/
}

void Reset()
{
	g_start = 0;
	g_time = 0;
	g_speed = 0;

	digitalWrite(MEAS_UNIT_LED_TWO, LOW);
	digitalWrite(MEAS_UNIT_LED_ONE, LOW);
}

void FssHandler()
{
	if(!g_interruptsEnabled)
	{
		return;
	}

	g_start = micros();
	digitalWrite(MEAS_UNIT_LED_ONE, HIGH);
}

void RssHandler()
{
	if (!g_interruptsEnabled)
	{
		return;
	}

	g_time = micros() - g_start;
	g_speed = SPEED_CONSTANT / static_cast<double>(g_time == 0 ? 1 : g_time) * MEGA;
	digitalWrite(MEAS_UNIT_LED_TWO, HIGH);
}

void ReceiveCommand()
{
	while (g_link.available())
	{
		unsigned char cmd = g_link.read();

		switch(cmd)
		{		
		case MEAS_STBY_COMMAND:
			{
			Stby();
			break;
			}
		case GET_SPEED_COMMAND:
			{
			SendSpeed();
			break;
			}
		case START_MEAS_COMMAND:
			{
			StartMeasuring();
			break;
			}
		case TEST_SPEED_COMMAND:
		{
			SetTestSpeed();
			break;
		}
		default: ;
		}
	}
}

void Stby()
{
	g_interruptsEnabled = false;
	Reset();	
}

void StartMeasuring()
{
	g_interruptsEnabled = true;
	ResetDebouncingTriggers();
}

void SendSpeed()
{
	g_link.write((const char*)&g_speed, sizeof(double));
}

void ResetDebouncingTriggers()
{
	digitalWrite(SS_TRIGGER_RESET_PORT, LOW);
	delay(10);
	digitalWrite(SS_TRIGGER_RESET_PORT, HIGH);
}

void SetTestSpeed()
{
	g_speed = TEST_SPEED_VAL;
}
