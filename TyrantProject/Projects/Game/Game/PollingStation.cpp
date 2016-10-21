#include "stdafx.h"
#include "PollingStation.h"

PollingStation* PollingStation::myInstance = new PollingStation();


PollingStation::PollingStation() : myPlayerUser(nullptr), myPlayerOpponent(nullptr)
{
}

PollingStation::~PollingStation()
{
}

PollingStation& PollingStation::GetInstance()
{
	return *myInstance;
}

void PollingStation::Destroy()
{
	SAFE_DELETE(myInstance);
}


Player* PollingStation::GetPlayerUser()
{
	return myPlayerUser;
}

Player* PollingStation::GetPlayerOpponent()
{
	return myPlayerOpponent;
}
