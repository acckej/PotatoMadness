#pragma once
#include "IArduinoWrapper.h"
#include "IAction.h"

class Sequenser
{
public:
	Sequenser(IArduinoWrapper* wrapper);



private:
	IArduinoWrapper* _wrapper;
};

