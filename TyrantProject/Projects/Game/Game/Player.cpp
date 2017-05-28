#include "stdafx.h"
#include "Player.h"
#include <time.h>

Vector2<float> deckOffsetPerCard(-0.01f, 0.01f);
Vector2<float> assaultCardStartPosition(-2.7f, -1.3f);
Vector2<float> structureCardStartPosition(-0.9f, -3.7f);
float playedCardsOffset = 1.8f;
float cardPlayLerpTime = 0.2f;


Player::Player() : myCurrentChosenCard(nullptr)
{
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
	myComander->SetPopupHitbox();

	myAssaultCards.Allocate(16);
	myStructureCards.Allocate(16);
	mySummonedCards.Allocate(255);

	myHand.Init(myPlayerType == ePlayerType::User);
	ShuffleDeck();	
	DrawCard();
	DrawCard();
	DrawCard();	
}

void Player::ToggleCardPopups(bool toggle)
{
	myComander->GetPopup().SetActive(toggle);
	for (int i = 0; i < myAssaultCards.Size(); ++i)
	{
		myAssaultCards[i]->GetPopup().SetActive(toggle);
	}
	for (int i = 0; i < myStructureCards.Size(); ++i)
	{
		myStructureCards[i]->GetPopup().SetActive(toggle);
	}
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
}

int Player::ChooseCardToPlay()
{
	DEBUG_ASSERT(myHand.HasCards(), "Can't choose a card with no cards in hand");

	if (myPlayerType == ePlayerType::User)
	{
		if(myHand.ChooseCardToPlay(myCurrentChosenCard) == true)
		{
			myHand.SetActive(false);
		}
	}
	else if (myPlayerType == ePlayerType::AI_Opponent)
	{
		myCurrentChosenCard = myHand.GetCards().GetLast();
	}


	if (myCurrentChosenCard != nullptr)
	{
		for (int i = 0; i < myOwnedCards.Size(); ++i)
		{
			if (myCurrentChosenCard == &myOwnedCards[i])
			{
				myCurrentChosenCard = nullptr;
				return i;
			}
		}
	}
	return -1;
}

Card* Player::SummonCard(const string& aCardToSummon)
{
	if (mySummonedCards.Size() >= 256)
	{
		return nullptr;
	}
	CardData* newCardData = CardFactory::GetInstance().GetCard(aCardToSummon);
	if (newCardData == nullptr)
	{
		return nullptr;
	}

	mySummonedCards.Add(Card(this));
	Card& newCard = mySummonedCards.GetLast();
	newCard.LoadCard(newCardData);
	
	Vector2<float> position;
	if (newCard.GetCardType() == eCardType::Assault)
	{
		position = assaultCardStartPosition;
		position.x += playedCardsOffset * myAssaultCards.Size();
		if (myPlayerType != ePlayerType::User)
		{
			position.y *= -1;
		}

		newCard.SetPosition(position);
		newCard.SetPopupHitbox();
		myAssaultCards.Add(&mySummonedCards.GetLast());
	}
	else if (newCard.GetCardType() == eCardType::Structure)
	{
		position = structureCardStartPosition;
		position.x += playedCardsOffset * myStructureCards.Size();
		if (myPlayerType != ePlayerType::User)
		{
			position.y *= -1.f;
		}

		newCard.SetPosition(position);
		newCard.SetPopupHitbox();
		myStructureCards.Add(&mySummonedCards.GetLast());
	}

	return &mySummonedCards.GetLast();
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
}

void Player::ShuffleDeck()
{
	srand(static_cast<unsigned int>(time(0)) + rand());
	if (myDeckCards.Size() < 1) return;

	CU::GrowingArray<int> indexes(myDeckCards.Size());
	for (int i = 0; i < myDeckCards.Size(); ++i)
	{
		indexes.Add(i);
	}

	CU::GrowingArray<Card*> unshuffledDeck = myDeckCards;
	Vector3<float> deckPosition;
	if (myPlayerType == ePlayerType::User)
	{
		deckPosition.Set(-5.35f, -2.0f, -0.11f);
	}
	else
	{
		deckPosition.Set(-5.35f, 3.4f, -0.11f);
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
	if (myDeckCards.Size() > 0 && myHand.GetCards().Size() < 3)
	{
		myHand.AddCard(myDeckCards.GetLast());
		myDeckCards.RemoveLast();
	}

	if (myHand.HasCards())
	{
		myHand.SetActive(true);
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