#pragma once
#include "Card.h"
#include "CardHand.h"


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
	void ToggleCardPopups(bool toggle);

	void Render();
	void DrawCard();

	int ChooseCardToPlay();
	Card* SummonCard(const string& aCardToSummon);

	inline bool CommanderIsDead();
	inline Player* GetOpponent();

	inline CU::GrowingArray<Card*>& GetAssaultCards();
	inline CU::GrowingArray<Card*>& GetStructureCards();
	inline Card* GetCommander();

private:
	void RepositionPlayedCards();
	void PlayCard(Card* aCard);
	void ShuffleDeck();
	
	CardHand myHand;
	CU::GrowingArray<Card*> myDeckCards;
	CU::GrowingArray<Card*> myAssaultCards;
	CU::GrowingArray<Card*> myStructureCards;
	CU::GrowingArray<Card> mySummonedCards;
	CU::VectorOnStack<Card, DECK_MAX_SIZE> myOwnedCards;
	ePlayerType myPlayerType;
	Card* myComander;
	Card* myCurrentChosenCard;
	Player* myOpponent;
};

inline bool Player::CommanderIsDead()
{
	return myComander->GetHealth() < 1;
}

inline Player* Player::GetOpponent()
{
	return myOpponent;
}

inline CU::GrowingArray<Card*>& Player::GetAssaultCards()
{
	return myAssaultCards;
}

inline CU::GrowingArray<Card*>& Player::GetStructureCards()
{
	return myStructureCards;
}

inline Card * Player::GetCommander()
{
	return myComander;
}
