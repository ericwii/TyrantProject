#pragma once

#include "TimeCounter.h"

class Timer
{
public:
	Timer();
	~Timer();

	void Update();
	void Start();
	void Stop();
	void Resume();

	inline const TimeCounter& GetTime() const;
	TimeCounter GetTimeSinceLastUpdate();

	inline const bool IsStopped() const;

private:
	LARGE_INTEGER myFrequency;
	LARGE_INTEGER myStartTime;
	LARGE_INTEGER myLastUpdateTime;
	LARGE_INTEGER myStopTime;

	TimeCounter time;
	TimeCounter timeSinceLastUpdate;

	double hours;
	double minutes;
	double seconds;
	double miliseconds;
	double microseconds;

	bool isStopped;
};