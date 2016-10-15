#include "Timer.h"



Timer::Timer()
{
	myStartTime.QuadPart = 0;
	isStopped = true;
}

Timer::~Timer()
{
}

void Timer::Start()
{
	QueryPerformanceCounter(&myStartTime);
	QueryPerformanceFrequency(&myFrequency);
	isStopped = false;
}

void Timer::Stop()
{
	isStopped = true;
	QueryPerformanceCounter(&myStopTime);
}

void Timer::Resume()
{
	if (myStartTime.QuadPart != 0 && isStopped == true)
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		myStartTime.QuadPart += (currentTime.QuadPart - myStopTime.QuadPart);
		isStopped = false;
	}
}

void Timer::Update()
{
	QueryPerformanceCounter(&myLastUpdateTime);

	if (isStopped == false)
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		time.Update(myStartTime, currentTime, myFrequency);
	}
}

inline const TimeCounter& Timer::GetTime() const
{
	return time;
}

TimeCounter Timer::GetTimeSinceLastUpdate()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	timeSinceLastUpdate.Update(myLastUpdateTime, currentTime, myFrequency);

	return timeSinceLastUpdate;
}

inline const bool Timer::IsStopped() const
{
	return isStopped;
}