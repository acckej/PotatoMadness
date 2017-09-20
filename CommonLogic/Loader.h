#pragma once
#include "IArduinoWrapper.h"


class Loader
{
public:
	Loader(IArduinoWrapper*);

	void Forward() const;
	void Reverse() const;

	void Stop() const;

	bool IsOverload() const;

	float GetCurrent() const;

	bool NoAmmo() const;

	bool IsRevCheckOn() const;
	bool IsFwCheckOn() const;
private:
	IArduinoWrapper* _wrapper;
};

