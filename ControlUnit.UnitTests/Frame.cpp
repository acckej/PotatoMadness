#include "stdafx.h"
#include "Frame.h"


Frame::Frame(): _currentFrame(0)
{
}

int Frame::AnalogRead(int port)
{
	return ReadPort(port, _analogReadPorts);
}

int Frame::DigitalRead(int port)
{
	return ReadPort(port, _digitalReadPorts);
}

float Frame::GetAtmPressure()
{
	return ReadSensor(_atmPressure);
}

float Frame::GetInternalTemp()
{
	return ReadSensor(_internalTemp);
}

float Frame::GetExternalTemp()
{
	return ReadSensor(_externalTemp);
}

float Frame::GetExternalHumidity()
{
	return ReadSensor(_externalHumidity);
}

void Frame::WritePort(int port, int value)
{
	auto found = _writtenValues.find(port);
		
	if (found == _writtenValues.end())
	{
		vector<PortValue> vals;
		vals.push_back({ _currentFrame, value });
		_writtenValues.insert(std::make_pair(port, value));
		return;
	}

	auto vals = found->second;
	vals.push_back({ _currentFrame, value });
}

float Frame::ReadSensor(vector<SensorValue> mapping)
{
	float result = 0;

	for (auto curr = mapping.begin(); curr != mapping.end(); ++curr)
	{
		result = curr->Value;
		if (curr->TimeFrame >= _currentFrame)
		{
			break;
		}
	}

	return result;
}

void Frame::AddPortMapping(int port, vector<PortValue> vals, map<int, vector<PortValue>> mapping)
{
	_writtenValues.insert(std::make_pair(port, vals));
}

void Frame::AddSensorValue(SensorValue val, vector<SensorValue> vals)
{
	vals.push_back(val);
}

void Frame::IncrementFrame()
{
	_currentFrame++;
}

void Frame::AddAnalogPortMapping(int port, vector<PortValue> vals)
{
	AddPortMapping(port, vals, _analogReadPorts);
}

void Frame::AddDigitalPortMapping(int port, vector<PortValue> vals)
{
	AddPortMapping(port, vals, _digitalReadPorts);
}

void Frame::AddAtmPressure(SensorValue val)
{
	AddSensorValue(val, _atmPressure);
}

void Frame::AddInternalTemp(SensorValue val)
{
	AddSensorValue(val, _internalTemp);
}

void Frame::AddExternalTemp(SensorValue val)
{
	AddSensorValue(val, _externalTemp);
}

void Frame::AddExternalHumidity(SensorValue val)
{
	AddSensorValue(val, _externalHumidity);
}

int Frame::ReadPort(int port, map<int, vector<PortValue>> portValues)
{
	auto found = portValues.find(port);

	if (found == portValues.end())
	{
		return 0;
	}

	auto vals = found->second;
	int result = 0;

	for (auto curr = vals.begin(); curr != vals.end(); ++curr)
	{
		result = curr->Value;
		if (curr->TimeFrame >= _currentFrame)
		{
			break;
		}
	}

	return result;
}


