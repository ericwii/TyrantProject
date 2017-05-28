#pragma once
#include "AbilityBase.h"

class Card;

enum eGamePhase
{
	Upkeep,
	Play,
	Priority,
	PreCombat,
	Combat,
	Cleanup,
};

enum eCombatState
{
	Setup,
	CalculateAttack,
	DoAtack
};

enum eAbilityMethod
{
	ePreCombat,
	ePriority,
	eCleanup
};

class Player;

class CardGameManager
{
public:
	 static bool Update(eGamePhase aCurrentPhase, Player& anActivePlayer, Player& aOtherPlayer);

	 void Upkeep(Player& anActivePlayer);
	 bool PlayCard(Player& anActivePlayer);
	 bool Priority(Player& anActivePlayer);
	 bool PreCombat(Player& anActivePlayer);
	 bool Combat(Player& anAttacker, Player& aDefender);
	 bool CleanUp(Player& anActivePlayer, Player& anOpponentPlayer);

private:
	CardGameManager();
	~CardGameManager();

	int UpdateCards(Player& aPlayer);

	bool AllActionsDone(Player& aPlayer, Player& aOtherPlayer);

	void RemoveDeadCards(Player& anActivePlayer, Player& anOpponentPlayer);
	bool UpdateAbilities(Card* aCard, eAbilityMethod aMethod);

	void CombatSetup(Player& anAttacker, Player& aDefender);
	bool CombatCalculations(Player& aDefender);
	bool CombatAttack();
	void AttackCard(Card* anAttacker, Card* aDefender);

private:

	static CardGameManager* instance;

	AttackData myCurrentAttackData;
	CU::VectorOnStack<AbilityBase*, 3> myCurrentAbilities;
	Player* myAttacker;
	Player* myDefender;
	eCombatState myCombatState;
	float myCurrentDelayBetweenAttackTargets;
	int myCurrentAssaultCardIndex;
	int myCurrentStructureCardIndex;
	int myCurrentAbilityIndex;
	int myCurrentAttackIndex = 0;
	int myCurrentAttackTargetIndex = 0;
	int myChosenCardIndex;
	bool myPhaseUpdateDone = false;
	bool myHasUpdatedCommander = false;
	bool myHasRemovedDeadCards = false;
	bool myIgnoreAttack = false;
	bool myHasPlayedCurrentAttackAnimation = false;
};

