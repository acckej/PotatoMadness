#pragma once

enum CheckResult {Passed, Interrupted, Failed};

class IHwCheck
{
public:
	virtual CheckResult Check();
};

