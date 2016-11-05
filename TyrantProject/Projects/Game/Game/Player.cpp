#include "stdafx.h"
#include "Player.h"

Vector2<float> deckOffsetPerCard(0.01f, 0.01f);


Player::Player()
{
}

Player::~Player()
{
}


void Player::Init(const string& aDeckXmlFile, ePlayerType aPlayerType)
{
	myPlayerType = aPlayerType;
	Vector3<float> deckPosition;
	Vector3<float> commanderPosition;

	if (myPlayerType == ePlayerType::User)
	{
		deckPosition.Set(-4.8f, -1.8f, -0.55f);
		commanderPosition.Set(-2.7f, -3.7f, 0);
	}
	else
	{
		deckPosition.Set(-4.8f, 2.97f, -0.55f);
		commanderPosition.Set(-2.7f, 3.7f, 0);
	}

	CU::VectorOnStack<CardData*, DECK_MAX_SIZE> cardDataList = CardFactory::GetInstance().GetDeck(aDeckXmlFile);
	myDeck.Clear();

	CU::Matrix44<float> cardOrientation = CU::Matrix44<float>::CreateRotateAroundY(PI);

	for (int i = 0; i < cardDataList.Size(); ++i)
	{
		myDeck.Add(Card());
		myDeck[i].LoadCard(cardDataList[i]);
		myDeck[i].SetOrientation(cardOrientation);

		myDeck[i].SetPosition(deckPosition + deckOffsetPerCard * static_cast<float>(i));
	}

	myComander = &myDeck[0];
	myComander->SetOrientation(CU::Matrix44<float>());
	myComander->SetPosition(commanderPosition);

	myAssaultCards.Allocate(16);
	myStructureCards.Allocate(16);

	myComander = &myDeck[0];
}

void Player::Update()
{

}

void Player::Render()
{
	for (int i = 0; i < myDeck.Size(); ++i)
	{
		myDeck[i].Render();
	}
}

