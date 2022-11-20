#include <SoftwareSerial.h>
#include "Definitions.h"
#include <LiquidCrystal_I2C.h>
#include "Constants.h"

SoftwareSerial g_link(TEST_MASTER_SERIAL_RX, TEST_MASTER_SERIAL_TX); // Rx, Tx
LiquidCrystal_I2C g_lcd(0x27, 20, 4); //0x3f

int g_count;

// the setup function runs once when you press reset or power the board
void setup()
{
	g_link.begin(SERIAL_SPEED);
	g_lcd.begin();
	g_lcd.backlight();

	//Serial.begin(SERIAL_SPEED);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	g_lcd.setCursor(0, 0);
	g_lcd.print(g_count);	

	g_link.write(TEST_SPEED_COMMAND);
	g_link.flush();		
	delay(MEAS_UNIT_RESPONSE_DELAY);

	g_link.write(GET_SPEED_COMMAND);
	g_link.flush();
	delay(MEAS_UNIT_RESPONSE_DELAY);

	unsigned char buf[sizeof(double)];

	auto bytesRead = 0;

	while (g_link.available())
	{
		auto ch = static_cast<unsigned char>(g_link.read());
		buf[bytesRead] = ch;
		bytesRead++;

		if (bytesRead >= sizeof(double))
		{
			const auto result = *reinterpret_cast<double*>(buf);
			
			g_lcd.setCursor(0, 1);
			g_lcd.print(result);
		}
	}
	//*/
	/*while (g_link.available())
	{
		g_lcd.setCursor(0, 1);
		g_lcd.print(g_link.read());
	}*/

	g_count++;
	delay(1000);
}
