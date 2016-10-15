#pragma once
#include <Query.h>

class Time
{
public:
	static void Update();
	static float DeltaTime();

private:
	Time();
	~Time();

	static Time instance;

	LARGE_INTEGER frequency;
	LARGE_INTEGER startTime;
	LARGE_INTEGER lastUpdateTime;
	bool initialized;
};
