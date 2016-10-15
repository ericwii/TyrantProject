#pragma once

#include <Query.h>

class TimeCounter
{
public:
	TimeCounter();
	~TimeCounter();

	void Update(LARGE_INTEGER aStartTime, LARGE_INTEGER aCurrentTime, LARGE_INTEGER aFrequency);

	unsigned int GetHours() const;
	unsigned int GetMinutes()const;
	unsigned int GetSeconds() const;
	unsigned int GetMiliseconds() const;
	unsigned int GetMicroseconds() const;

	double GetTotalHours() const;
	double GetTotalMinutes()const;
	double GetTotalSeconds() const;
	double GetTotalMiliseconds() const;
	double GetTotalMicroseconds() const;

private:
	double hours;
	double minutes;
	double seconds;
	double miliseconds;
	double microseconds;
};
