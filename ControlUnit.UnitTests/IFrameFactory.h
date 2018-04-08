#pragma once
#include "Frame.h"

class IFrameFactory
{
public:
	virtual ~IFrameFactory() = default;
	IFrameFactory(int frameDelay);
	
	virtual Frame* GetTestFrame();
protected:
	int _frameDelay;
};

