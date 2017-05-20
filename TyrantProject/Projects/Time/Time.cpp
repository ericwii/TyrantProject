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

	deltaTime = min(max(deltaTime, 0.00001f),0.1f);

	return deltaTime * instance.timeScale;
}

void Time::SetTimeScale(float timeScale)
{
	instance.timeScale = timeScale;
}


//Private methods

Time::Time() : initialized(false), timeScale(1.f)
{
	QueryPerformanceFrequency(&instance.frequency);
	QueryPerformanceCounter(&instance.startTime);

	initialized = false;
}

Time::~Time()
{
}