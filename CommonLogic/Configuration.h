#pragma once
class Configuration
{
public:
	Configuration();

	int GetLoaderForwardFanTime();
	int GetLoaderReverseFanTime();
	
private:
	int _loaderForwardFanTime;
	int _loaderReverseFanTime;
};

