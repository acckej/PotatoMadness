#pragma once

#include <map>
#include "PortValues.h"
#include <vector>

using namespace std;

class Frame
{
public:
	Frame(int frameDelay);

	int AnalogRead(int port) const;
	int DigitalRead(int port) const;

	float GetAtmPressure() const;
	float GetInternalTemp() const;
	float GetExternalTemp() const;
	float GetExternalHumidity() const;

	void WritePort(int port, int value);

	void IncrementFrame();

	void AddAnalogPortMapping(int, vector<PortValue> vals);
	void AddDigitalPortMapping(int, vector<PortValue> vals);

	void AddAtmPressure(SensorValue val) const;
	void AddInternalTemp(SensorValue val) const;
	void AddExternalTemp(SensorValue val) const;
	void AddExternalHumidity(SensorValue val) const;

	long GetMilliseconds() const;
private:
	int ReadPort(int port, map<int, vector<PortValue>> portValues) const;
	float ReadSensor(vector<SensorValue> mapping) const;	
	static void AddSensorValue(SensorValue val, vector<SensorValue> vals);

	int _frameDelay;
	int _currentFrame;

	map<int, vector<PortValue>> _analogReadPorts;
	map<int, vector<PortValue>> _digitalReadPorts;

	vector<SensorValue> _atmPressure;
	vector<SensorValue> _internalTemp;
	vector<SensorValue> _externalTemp;
	vector<SensorValue> _externalHumidity;

	map<int, vector<PortValue>> _writtenValues;
};

