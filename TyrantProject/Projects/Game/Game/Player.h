#pragma once
#include "Card.h"


enum eGamePhase
{
	Upkeep,
	Play,
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
public:
	Player();
	~Player();

	void Init(const string& aDeckXmlFile, ePlayerType aPlayerType);

	bool Update(eGamePhase aPhase);
	void Render();

private:
	bool UpdateUpkeep();
	bool UpdatePlay();
	bool UpdateCombat();
	bool UpdateCleanup();
	void PlayCard(Card* aCard);
	void ShuffleDeck();

	CU::VectorOnStack<Card, DECK_MAX_SIZE> myOwnedCards;
	ePlayerType myPlayerType;
	Card* myComander;
	CU::GrowingArray<Card*> myDeckCards;
	CU::GrowingArray<Card*> myAssaultCards;
	CU::GrowingArray<Card*> myStructureCards;
};

