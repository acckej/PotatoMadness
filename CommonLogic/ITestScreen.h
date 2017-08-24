#pragma once
class ITestScreen
{
public:
	ITestScreen();
	~ITestScreen();

	void PutTestMessage(char* message, char line);

	void Refresh();
};

