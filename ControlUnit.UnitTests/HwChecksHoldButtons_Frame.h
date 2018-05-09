#pragma once

#include "IFrameFactory.h"
#include "Constants.h"

class HwTestHoldButtons_Config : public IConfiguration
{
public:
	int GetLoaderForwardFanTime() override
	{
		return 2000;
	};
};

class HwChecksHoldButtons_Frame : public IFrameFactory
{
public:
	explicit HwChecksHoldButtons_Frame(int frameDelay)
		: IFrameFactory(frameDelay)
	{
	}

	Frame* GetTestFrame() override
	{
		auto result = new Frame(_frameDelay, new HwTestHoldButtons_Config());

		vector<PortValue> btn1 = {
			{ 0, 0 },
		{ 1, 1 }		
		};
		result->AddDigitalPortMapping(BTN4_PORT, btn1);		

		return result;
	}
};


