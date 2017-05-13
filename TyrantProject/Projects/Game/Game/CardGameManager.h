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
	 void CleanUp(Player& anActivePlayer, Player& anOpponentPlayer);

private:
	CardGameManager();
	~CardGameManager();

	int UpdateCards(Player& aPlayer);

	bool AllActionsDone(Player& aPlayer, Player& aOtherPlayer);

	static CardGameManager* instance;

	Player* myAttacker;
	Player* myDefender;
	Card* myChoosenCard;
	int myCurrentAssaultCardIndex;
	int myCurrentStructureCardIndex;
	int myCurrentAbilityIndex;
	bool myPhaseUpdateDone = false;
	bool hasUpdatedCommander = false;
};

