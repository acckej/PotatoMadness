#pragma once
#include "TypeDefinitions.h"

class IArduinoWrapper  
{
public:
	virtual ArduinoInt DigitalRead(ArduinoUInt port);
	virtual void DigitalWrite(ArduinoUInt port, ArduinoInt value);
	
	virtual ArduinoInt AnalogRead(ArduinoUInt port);
	virtual void AnalogWrite(ArduinoUInt port, ArduinoInt value);

	virtual void Delay(ArduinoULong delay);
};

