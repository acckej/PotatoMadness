#include "stdafx.h"
#include "Frame.h"


Frame::Frame(int frameDelay): _currentFrame(0)
{
	_frameDelay = frameDelay;
}

int Frame::AnalogRead(int port) const
{
	return ReadPort(port, _analogReadPorts);
}

int Frame::DigitalRead(int port) const
{
	return ReadPort(port, _digitalReadPorts);
}

float Frame::GetAtmPressure() const
{
	return ReadSensor(_atmPressure);
}

float Frame::GetInternalTemp() const
{
	return ReadSensor(_internalTemp);
}

float Frame::GetExternalTemp() const
{
	return ReadSensor(_externalTemp);
}

float Frame::GetExternalHumidity() const
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

float Frame::ReadSensor(vector<SensorValue> mapping) const
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
	_analogReadPorts.insert(std::make_pair(port, vals));
}

void Frame::AddDigitalPortMapping(int port, vector<PortValue> vals)
{
	_digitalReadPorts.insert(std::make_pair(port, vals));
}

void Frame::AddAtmPressure(SensorValue val) const
{
	AddSensorValue(val, _atmPressure);
}

void Frame::AddInternalTemp(SensorValue val) const
{
	AddSensorValue(val, _internalTemp);
}

void Frame::AddExternalTemp(SensorValue val) const
{
	AddSensorValue(val, _externalTemp);
}

void Frame::AddExternalHumidity(SensorValue val) const
{
	AddSensorValue(val, _externalHumidity);
}

long Frame::GetMilliseconds() const
{
	return _currentFrame * _frameDelay;
}

int Frame::ReadPort(int port, map<int, vector<PortValue>> portValues) const
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


