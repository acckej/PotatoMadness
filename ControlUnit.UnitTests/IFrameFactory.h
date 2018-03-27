#pragma once
#include "Frame.h"

class IFrameFactory
{
public:
	virtual ~IFrameFactory() = default;
	IFrameFactory();
	
	virtual Frame* GetTestFrame();	
};

