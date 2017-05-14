#pragma once

class Card;

enum eGamePhase
{
	Upkeep,
	Play,
	PreCombat,
	Combat,
	Cleanup
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
	bool UpdateAbilities(Card* aCard, bool cleanUp = false);

private:
	static CardGameManager* instance;

	CU::VectorOnStack<AbilityBase*, 3> myCurrentAbilities;
	Player* myAttacker;
	Player* myDefender;
	Card* myChoosenCard;
	int myCurrentAssaultCardIndex;
	int myCurrentStructureCardIndex;
	int myCurrentAbilityIndex;
	bool myPhaseUpdateDone = false;
	bool myHasUpdatedCommander = false;
	bool myHasRemovedDeadCards = false;
};

