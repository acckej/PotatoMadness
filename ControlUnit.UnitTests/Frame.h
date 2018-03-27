#pragma once

#include <map>
#include "PortValues.h"
#include <vector>

using namespace std;

class Frame
{
public:
	Frame();

	int AnalogRead(int port);
	int DigitalRead(int port);

	float GetAtmPressure();
	float GetInternalTemp();
	float GetExternalTemp();
	float GetExternalHumidity();

	void WritePort(int port, int value);

	void IncrementFrame();

	void AddAnalogPortMapping(int, vector<PortValue> vals);
	void AddDigitalPortMapping(int, vector<PortValue> vals);

	void AddAtmPressure(SensorValue val);
	void AddInternalTemp(SensorValue val);
	void AddExternalTemp(SensorValue val);
	void AddExternalHumidity(SensorValue val);
private:
	int ReadPort(int port, map<int, vector<PortValue>> portValues);
	float ReadSensor(vector<SensorValue> mapping);
	void AddPortMapping(int port, vector<PortValue> vals, map<int, vector<PortValue>> mapping);
	void AddSensorValue(SensorValue val, vector<SensorValue> vals);

	int _currentFrame;

	map<int, vector<PortValue>> _analogReadPorts;
	map<int, vector<PortValue>> _digitalReadPorts;

	vector<SensorValue> _atmPressure;
	vector<SensorValue> _internalTemp;
	vector<SensorValue> _externalTemp;
	vector<SensorValue> _externalHumidity;

	map<int, vector<PortValue>> _writtenValues;
};

