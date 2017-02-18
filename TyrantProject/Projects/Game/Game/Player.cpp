#include "stdafx.h"
#include "Player.h"
#include "CombatManager.h"
#include <time.h>

Vector2<float> deckOffsetPerCard(-0.01f, 0.01f);
Vector2<float> assaultCardStartPosition(-2.7f, -1.3f);
Vector2<float> structureCardStartPosition(-0.9f, -3.7f);
float playedCardsOffset = 1.8f;
float cardPlayLerpTime = 0.2f;


Player::Player()
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
	myOwnedCards.Add(Card());
	myOwnedCards[0].LoadCard(cardDataList[0]);

	CU::Matrix44<float> cardOrientation = CU::Matrix44<float>::CreateRotateAroundY(PI);

	for (int i = 1; i < cardDataList.Size(); ++i)
	{
		myOwnedCards.Add(Card());
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
}

bool Player::Update(eGamePhase aPhase)
{
	float deltaTime = Time::DeltaTime();
	for (int i = 0; i < myOwnedCards.Size(); ++i)
	{
		myOwnedCards[i].Update(deltaTime);
	}

	switch (aPhase)
	{
		case (Upkeep):
		{
			return UpdateUpkeep();
			break;
		}
		case (Play) :
		{
			return UpdatePlay();
			break;
		}
		case (PreCombat) :
		{
			return UpdatePrecombat();
			break;
		}
		case (Combat) :
		{
			return UpdateCombat();
			break;
		}
		case (Cleanup) :
		{
			return UpdateCleanup();
			break;
		}
	    default:
		{
			return false;
		}
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




//Private methods

bool Player::UpdateUpkeep()
{
	for (int i = 0; i < myAssaultCards.Size(); ++i)
	{
		myAssaultCards[i]->LowerCooldown();
	}
	for (int i = 0; i < myStructureCards.Size(); ++i)
	{
		myStructureCards[i]->LowerCooldown();
	}

	return false;
}


Card* myPlayedCard = nullptr;
bool Player::UpdatePlay()
{
	if (myPlayedCard == nullptr)
	{
		if (myDeckCards.Size() == 0) return false;

		if (myPlayerType == ePlayerType::User)
		{
			if (InputManager::Mouse.WasButtonJustPressed(eMouseButton::LEFTBUTTON))
			{
				PlayCard(myDeckCards.GetLast());
			}
		}
		else if (myPlayerType == ePlayerType::AI_Opponent)
		{
			PlayCard(myDeckCards.GetLast());
		}
	}

	if (myPlayedCard != nullptr && myPlayedCard->IsLerping() == false)
	{
		myPlayedCard = nullptr;
		return false;
	}

	return true;
}

bool Player::UpdatePrecombat()
{
	return false;
}

bool Player::UpdateCombat()
{
	CombatManager::DoCombat(this, myOpponent);
	return false;
}

bool Player::UpdateCleanup()
{
	return false;
}




void Player::PlayCard(Card* aCard)
{
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
			position.y *= -1;
		}

		aCard->SetPosition(position);
		myStructureCards.Add(aCard);
	}

	CU::Matrix44<float> lerpTarget;
	lerpTarget.SetPosition(position);

	myPlayedCard = aCard;
	myPlayedCard->LerpToOrientation(lerpTarget, cardPlayLerpTime);
	myDeckCards.RemoveNonCyclic(aCard);
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