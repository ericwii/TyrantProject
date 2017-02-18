#pragma once
#include "Card.h"


enum eGamePhase
{
	Upkeep,
	Play,
	PreCombat,
	Combat,
	Cleanup
};

enum class ePlayerType
{
	User,
	AI_Opponent,
	Player_Opponent
};


class Player
{
	friend class CombatManager;

public:
	Player();
	~Player();

	void Init(const string& aDeckXmlFile, ePlayerType aPlayerType, Player* anOpponent);

	bool Update(eGamePhase aPhase);
	void Render();

private:
	bool UpdateUpkeep();
	bool UpdatePlay();
	bool UpdatePrecombat();
	bool UpdateCombat();
	bool UpdateCleanup();
	void PlayCard(Card* aCard);
	void ShuffleDeck();

	CU::GrowingArray<Card*> myDeckCards;
	CU::GrowingArray<Card*> myAssaultCards;
	CU::GrowingArray<Card*> myStructureCards;
	CU::VectorOnStack<Card, DECK_MAX_SIZE> myOwnedCards;
	ePlayerType myPlayerType;
	Card* myComander;
	Player* myOpponent;
};

