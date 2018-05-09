#pragma once

#include "IFrameFactory.h"
#include "Constants.h"

class HwTest_Config : public IConfiguration
{
public:
	int GetLoaderForwardFanTime() override
	{
		return 2000;
	};
};

class HwChecksTest_Frame : public IFrameFactory
{
public:
	explicit HwChecksTest_Frame(int frameDelay)
		: IFrameFactory(frameDelay)
	{
	}

	Frame* GetTestFrame() override
	{
		auto result = new Frame(_frameDelay, new HwTest_Config());

		vector<PortValue> btn1 = {
			{ 0, 0 },
			{ 1, 1 },
			{ 2, 0 },
			{ 3, 0 },
			{ 20, 1 },
			{ 21, 0 }
		};
		result->AddDigitalPortMapping(BTN4_PORT, btn1);

		vector<PortValue> btn2 = {
			{ 0, 0 },
			{ 10, 1 },
			{ 11, 0 },
			{ 20, 1 },
			{ 21, 0 }
		};
		result->AddDigitalPortMapping(BTN1_PORT, btn2);		

		/*vector<PortValue> fwCheck = {
			{ 0, 0 },
		{ 1, 1 },
		{ 2, 1 },
		{ 3, 1 },
		{ 4, 0 },
		{ 80, 1 }
		};
		result->AddDigitalPortMapping(LDR_FW_CHECK_PORT, fwCheck);

		vector<PortValue> revCheck = {
			{ 0, 0 },
		{ 1, 0 },
		{ 2, 0 },
		{ 3, 0 },
		{ 4, 0 },
		{ 40, 1 },
		{ 90, 0 }
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

		vector<PortValue> pressure = {
			{ 0, 0 },
		{ 40, 403 }
		};
		result->AddAnalogPortMapping(RECEIVER_PRESSURE_PORT, pressure);

		vector<PortValue> ammo = {
			{ 0, 1 }
		};
		result->AddDigitalPortMapping(AMMO_SENSOR_PORT, ammo);

		result->AddAtmPressure({ 0, 0 });
		result->AddAtmPressure({ 40, 101.325f });

		result->AddExternalHumidity({ 0, 0 });
		result->AddExternalHumidity({ 40, 0.65f });

		result->AddExternalTemp({ 0, 0 });
		result->AddExternalTemp({ 40, 25.0f });*/

		return result;
	}
};


