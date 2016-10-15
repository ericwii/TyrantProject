#include "Time.h"

Time Time::instance = Time();


void Time::Update()
{
	QueryPerformanceCounter(&instance.lastUpdateTime);
}

float Time::DeltaTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	float deltaTime(static_cast<float>((currentTime.QuadPart - instance.lastUpdateTime.QuadPart)) / instance.frequency.QuadPart);

	deltaTime = min(max(deltaTime, 0.001f),0.3f);

	return deltaTime;
}


//Private methods

Time::Time()
{
	QueryPerformanceFrequency(&instance.frequency);
	QueryPerformanceCounter(&instance.startTime);

	initialized = false;
}

Time::~Time()
{
}