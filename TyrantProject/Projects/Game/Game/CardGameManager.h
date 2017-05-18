#pragma once
#include "AbilityBase.h"

class Card;

enum eGamePhase
{
	Upkeep,
	Play,
	PreCombat,
	Combat,
	Cleanup
};

enum eCombatState
{
	Setup,
	CalculateAttack,
	DoAtack
};

enum eAbilityMethod
{
	eCleanup,
	ePreCombat,
	eCalculateAttack
};

class Player;

class CardGameManager
{
public:
	 static bool Update(eGamePhase aCurrentPhase, Player& anActivePlayer, Player& aOtherPlayer);

	 void Upkeep(Player& anActivePlayer);
	 bool PlayCard(Player& anActivePlayer);
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

	bool CombatSetup(Player& anAttacker, Player& aDefender);
	bool CombatCalculations(Player& aDefender);
	bool CombatAttack();
	void AttackCard(Card* anAttacker, Card* aDefender);

private:

	static CardGameManager* instance;

	AttackData myCurrentAttackData;
	CU::VectorOnStack<AbilityBase*, 3> myCurrentAbilities;
	Player* myAttacker;
	Player* myDefender;
	Card* myChoosenCard;
	eCombatState myCombatState;
	int myCurrentAssaultCardIndex;
	int myCurrentStructureCardIndex;
	int myCurrentAbilityIndex;
	int myCurrentAttackIndex = 0;
	bool myPhaseUpdateDone = false;
	bool myHasUpdatedCommander = false;
	bool myHasRemovedDeadCards = false;
};

