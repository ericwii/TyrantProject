#pragma once
#include "Card.h"

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

	void Update();
	void Render();

private:
	CU::VectorOnStack<Card, DECK_MAX_SIZE> myDeck;

	ePlayerType myPlayerType;
	Card* myComander;
	CU::GrowingArray<Card*> myAssaultCards;
	CU::GrowingArray<Card*> myStructureCards;
};

