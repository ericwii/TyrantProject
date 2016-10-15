#include "TimeCounter.h"

TimeCounter::TimeCounter()
{
	hours = 0;
	minutes = 0;
	seconds = 0;
	miliseconds = 0;
	microseconds = 0;
}

TimeCounter::~TimeCounter()
{
}


void TimeCounter::Update(LARGE_INTEGER aStartTime, LARGE_INTEGER aCurrentTime, LARGE_INTEGER aFrequency)
{
	microseconds = (aCurrentTime.QuadPart - aStartTime.QuadPart) * (1000000.0 / aFrequency.QuadPart);

	miliseconds = microseconds * 0.001;
	seconds = miliseconds * 0.001;
	minutes = seconds / 60;
	hours = minutes / 60;
}


unsigned int TimeCounter::GetHours()  const
{
	return (static_cast<unsigned int>(hours));
}

unsigned int TimeCounter::GetMinutes()  const
{
	return (static_cast<unsigned int>(minutes) % 60);
}

unsigned int TimeCounter::GetSeconds()  const
{
	return (static_cast<unsigned int>(seconds) % 60);
}

unsigned int TimeCounter::GetMiliseconds()  const
{
	return (static_cast<unsigned int>(miliseconds) % 1000);
}

unsigned int TimeCounter::GetMicroseconds()  const
{
	return (static_cast<unsigned int>(microseconds) % 1000000);
}


double TimeCounter::GetTotalHours() const
{
	return (hours);
}

double TimeCounter::GetTotalMinutes()const
{
	return (minutes);
}

double TimeCounter::GetTotalSeconds() const
{
	return (seconds);
}

double TimeCounter::GetTotalMiliseconds() const
{
	return (miliseconds);
}

double TimeCounter::GetTotalMicroseconds() const
{
	return (microseconds);
}