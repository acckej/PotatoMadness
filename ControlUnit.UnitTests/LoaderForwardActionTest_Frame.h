#pragma once
#include "IFrameFactory.h"
#include "Constants.h"

class LoaderForwardActionTest_Config : public IConfiguration
{
public:
	int GetLoaderForwardFanTime() override
	{
		return 2000;
	};
};

class LoaderForwardActionTest_Frame : public IFrameFactory
{
public:
	explicit LoaderForwardActionTest_Frame(int frameDelay)
		: IFrameFactory(frameDelay)
	{
	}

	Frame* GetTestFrame() override
	{
		auto result = new Frame(_frameDelay, new LoaderForwardActionTest_Config());

		vector<PortValue> btn1 = {
			{0, 0},
			{1, 1},
			{2, 1},
			{3, 0},
			{4, 0}
		};
		result->AddDigitalPortMapping(BTN1_PORT, btn1);

		vector<PortValue> fwCheck = {
			{ 0, 0 },
			{ 1, 1 },
			{ 2, 1 },
			{ 3, 1 },
			{ 4, 1 }
		};
		result->AddDigitalPortMapping(LDR_FW_CHECK_PORT, fwCheck);

		vector<PortValue> revCheck = {
			{ 0, 0 },
			{ 1, 0 },
			{ 2, 0 },
			{ 3, 0 },
			{ 4, 0 }
		};
		result->AddDigitalPortMapping(LDR_REV_CHECK_PORT, revCheck);

		vector<PortValue> voltage = {
			{ 0, 878 },
			{ 1, 878 },
			{ 2, 878 },
			{ 3, 878 },
			{ 4, 878 }
		};
		result->AddAnalogPortMapping(VOLTAGE_PORT, voltage);

		return result;
	}
};
