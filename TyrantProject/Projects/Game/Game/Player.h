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
	friend class CardGameManager;

public:
	Player();
	~Player();

	void Init(const string& aDeckXmlFile, ePlayerType aPlayerType, Player* anOpponent);

	void Render();

	int ChooseCardToPlay();

	inline bool CommanderIsDead();
	inline Player* GetOpponent();

private:
	void RepositionPlayedCards();
	void PlayCard(Card* aCard);
	void ShuffleDeck();
	void UpdateHand();

	CU::GrowingArray<Card*> myHand;
	CU::GrowingArray<Card*> myDeckCards;
	CU::GrowingArray<Card*> myAssaultCards;
	CU::GrowingArray<Card*> myStructureCards;
	CU::VectorOnStack<Card, DECK_MAX_SIZE> myOwnedCards;
	ePlayerType myPlayerType;
	Card* myComander;
	Player* myOpponent;

	bool myShouldRenderhand;
};

inline bool Player::CommanderIsDead()
{
	return myComander->GetHealth() < 1;
}

inline Player* Player::GetOpponent()
{
	return myOpponent;
}