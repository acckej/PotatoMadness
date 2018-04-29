#pragma once

#include <map>
#include "PortValues.h"
#include <vector>
#include "Configuration.h"

using namespace std;

class Frame
{
public:
	Frame(int frameDelay, IConfiguration* config);
	~Frame();

	int AnalogRead(int port);
	int DigitalRead(int port);

	float GetAtmPressure() const;
	float GetInternalTemp() const;
	float GetExternalTemp() const;
	float GetExternalHumidity() const;

	void WritePort(int port, int value);

	void IncrementFrame();

	void AddAnalogPortMapping(int, vector<PortValue> vals);
	void AddDigitalPortMapping(int, vector<PortValue> vals);

	void AddAtmPressure(SensorValue val);
	void AddInternalTemp(SensorValue val);
	void AddExternalTemp(SensorValue val);
	void AddExternalHumidity(SensorValue val);

	long GetMilliseconds();

	void AddMilliseconds(int millis);

	IConfiguration* GetConfiguration() const;
private:
	int ReadPort(int port, map<int, vector<PortValue>>* portValues) const;
	float ReadSensor(vector<SensorValue> mapping) const;	
	static void AddSensorValue(SensorValue val, vector<SensorValue>* vals);

	int _frameDelay;
	int _currentFrame;

	int _millis;

	map<int, vector<PortValue>> _analogReadPorts;
	map<int, vector<PortValue>> _digitalReadPorts;

	vector<SensorValue> _atmPressure;
	vector<SensorValue> _internalTemp;
	vector<SensorValue> _externalTemp;
	vector<SensorValue> _externalHumidity;

	map<int, vector<PortValue>> _writtenValues;

	IConfiguration* _configuration;
};

