#pragma once

class Player;

class CombatManager
{
public:
	static void DoCombat(Player* anAttacker, Player* aDefender);

private:
	CombatManager();
	~CombatManager();
	static CombatManager* instance;

	Player* myAttacker;
	Player* myDefender;
};

