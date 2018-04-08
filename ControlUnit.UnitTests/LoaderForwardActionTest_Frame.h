#pragma once
#include "IFrameFactory.h"
#include "Constants.h"

class LoaderForwardActionTest_Frame : public IFrameFactory
{
public:
	explicit LoaderForwardActionTest_Frame(int frameDelay)
		: IFrameFactory(frameDelay)
	{
	}

	Frame* GetTestFrame() override
	{
		auto result = new Frame(_frameDelay);

		vector<PortValue> btn1 = {
			{0, 0},
			{1, 1},
			{2, 1},
			{3, 0},
			{4, 0}
		};
		result->AddDigitalPortMapping(BTN1_PORT, btn1);

		return result;
	}
};
