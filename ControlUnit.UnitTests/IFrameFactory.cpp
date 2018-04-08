#include "stdafx.h"
#include "IFrameFactory.h"


IFrameFactory::IFrameFactory(int frameDelay)
{
	_frameDelay = frameDelay;
}

Frame* IFrameFactory::GetTestFrame()
{
	return nullptr;
}

