#pragma once

#define Test

#ifdef Test

#define ArduinoInt int
#define ArduinoUInt int
#define ArduinoDouble float
#define ArduinoULong unsigned long

#define ARDUINO_LOW 0
#define ARDUINO_HIGH 1

#endif

#ifdef Arduino

#define ArduinoInt int
#define ArduinoUInt int
#define ArduinoDouble float
#define ArduinoULong unsigned long

#define ARDUINO_LOW LOW
#define ARDUINO_HIGH HIGH

#endif


