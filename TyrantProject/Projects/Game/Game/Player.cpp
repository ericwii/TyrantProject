#include "stdafx.h"
#include "Player.h"
#include <time.h>

Vector2<float> deckOffsetPerCard(-0.01f, 0.01f);
Vector2<float> assaultCardStartPosition(-2.7f, -1.3f);
Vector2<float> structureCardStartPosition(-0.9f, -3.7f);
float playedCardsOffset = 1.8f;
float cardPlayLerpTime = 0.2f;


Player::Player()
{
	myShouldRenderhand = false;
}

Player::~Player()
{
}


void Player::Init(const string& aDeckXmlFile, ePlayerType aPlayerType, Player* anOpponent)
{
	myOpponent = anOpponent;
	myPlayerType = aPlayerType;
	Vector3<float> commanderPosition(-2.7f, -3.7f, 0);

	if (myPlayerType != ePlayerType::User)
	{
		commanderPosition.y *= -1.f;
	}


	CU::VectorOnStack<CardData*, DECK_MAX_SIZE> cardDataList = CardFactory::GetInstance().GetDeck(aDeckXmlFile);
	myDeckCards.Allocate(DECK_MAX_SIZE);
	myOwnedCards.Clear();
	myOwnedCards.Add(Card(this));
	myOwnedCards[0].LoadCard(cardDataList[0]);

	CU::Matrix44<float> cardOrientation = CU::Matrix44<float>::CreateRotateAroundY(PI);

	for (int i = 1; i < cardDataList.Size(); ++i)
	{
		myOwnedCards.Add(Card(this));
		myOwnedCards[i].LoadCard(cardDataList[i]);

		myDeckCards.Add(&myOwnedCards.GetLast());
		myDeckCards[i-1]->SetOrientation(cardOrientation);
	}

	myComander = &myOwnedCards[0];
	myComander->SetOrientation(CU::Matrix44<float>());
	myComander->SetPosition(commanderPosition);

	myAssaultCards.Allocate(16);
	myStructureCards.Allocate(16);

	ShuffleDeck();	
	DrawCard();
	DrawCard();
	DrawCard();	
}

void Player::Render()
{
	myComander->Render();
	for (int i = 0; i < myDeckCards.Size(); ++i)
	{
		myDeckCards[i]->Render();
	}
	for (int i = 0; i < myAssaultCards.Size(); ++i)
	{
		myAssaultCards[i]->Render();
	}
	for (int i = 0; i < myStructureCards.Size(); ++i)
	{
		myStructureCards[i]->Render();
	}

	if (myPlayerType == ePlayerType::User && myShouldRenderhand == true)
	{
		myHand.Render();
	}
}

bool Player::ChooseCardToPlay(Card*& chosenCard)
{
	DEBUG_ASSERT(myHand.HasCards(), "Can't choose a card with no cards in hand");

	if (myPlayerType == ePlayerType::User)
	{
		myShouldRenderhand = true;
		if(myHand.ChooseCardToPlay(chosenCard) == true)
		{
			myShouldRenderhand = false;
			return true;
		}
	}
	else if (myPlayerType == ePlayerType::AI_Opponent)
	{
		chosenCard = myHand.GetCards().GetLast();
		return true;
	}

	return false;
}




//Private methods

void Player::PlayCard(Card* aCard)
{
	aCard->SetOrientation(CU::Matrix44<float>::CreateRotateAroundY(PI));

	Vector2<float> position;
	if (aCard->GetCardType() == eCardType::Assault)
	{
		position = assaultCardStartPosition;
		position.x += playedCardsOffset * myAssaultCards.Size();
		if (myPlayerType != ePlayerType::User)
		{
			position.y *= -1;
		}

		aCard->SetPosition(position);
		myAssaultCards.Add(aCard);
	}
	if (aCard->GetCardType() == eCardType::Structure)
	{
		position = structureCardStartPosition;
		position.x += playedCardsOffset * myStructureCards.Size();
		if (myPlayerType != ePlayerType::User)
		{
			position.y *= -1.f;
		}

		aCard->SetPosition(position);
		myStructureCards.Add(aCard);
	}

	CU::Matrix44<float> lerpTarget;
	lerpTarget.SetPosition(position);
	
	aCard->LerpToOrientation(lerpTarget, cardPlayLerpTime);

	myHand.RemoveCard(aCard);
	if (aCard != nullptr)
	{
		DrawCard();
	}
}

void Player::ShuffleDeck()
{
	srand(static_cast<unsigned int>(time(0)) + rand());

	CU::GrowingArray<int> indexes(myDeckCards.Size());
	for (int i = 0; i < myDeckCards.Size(); ++i)
	{
		indexes.Add(i);
	}

	CU::GrowingArray<Card*> unshuffledDeck = myDeckCards;
	Vector3<float> deckPosition;
	if (myPlayerType == ePlayerType::User)
	{
		deckPosition.Set(-4.77f, -1.8f, -0.55f);
	}
	else
	{
		deckPosition.Set(-4.8f, 2.97f, -0.55f);
	}

	int currentRandomIndex;
	int currentIndex;
	for (int i = 0; i < myDeckCards.Size(); ++i)
	{
		currentRandomIndex = rand() % indexes.Size();
		currentIndex = indexes[currentRandomIndex];
		indexes.RemoveCyclicAtIndex(currentRandomIndex);

		myDeckCards[i] = unshuffledDeck[currentIndex];
		myDeckCards[i]->SetPosition(deckPosition + deckOffsetPerCard * static_cast<float>(i));
	}
}

void Player::DrawCard()
{
	if (myDeckCards.Size() > 0)
	{
		myHand.AddCard(myDeckCards.GetLast());
		myDeckCards.RemoveLast();
	}
}

void Player::RepositionPlayedCards()
{
	Vector3<float> currentPosition = assaultCardStartPosition;
	Vector3<float> currentStructurePosition = structureCardStartPosition;
	if (myPlayerType != ePlayerType::User)
	{
		currentPosition.y *= -1.f;
		currentStructurePosition.y *= -1.0f;
	}

	for (int i = 0; i < myAssaultCards.Size(); ++i)
	{
		myAssaultCards[i]->SetPosition(currentPosition);
		currentPosition.x += playedCardsOffset;
	}

	for (int i = 0; i < myStructureCards.Size(); ++i)
	{
		myStructureCards[i]->SetPosition(currentStructurePosition);
		currentStructurePosition.x += playedCardsOffset;
	}
}