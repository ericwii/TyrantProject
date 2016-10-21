#pragma once

class Player;

class PollingStation
{
	static PollingStation& GetInstance();
	static void Destroy();



	Player* GetPlayerUser();
	Player* GetPlayerOpponent();


private:
	PollingStation();
	~PollingStation();

	Player* myPlayerUser;
	Player* myPlayerOpponent;

	static PollingStation* myInstance;
};

