#pragma once
#include "Card.h"

class Player
{
public:
	Player();
	~Player();

	void InitDeck(const string& anXmlFile);

	void Update();
	void Render();

private:
	CU::VectorOnStack<Card, DECK_MAX_SIZE> myDeck;

	Card* myComander;
	CU::GrowingArray<Card*> myAssaultCards;
	CU::GrowingArray<Card*> myStructureCards;
};

