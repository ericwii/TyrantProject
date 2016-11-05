#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}

Player::~Player()
{
}


void Player::InitDeck(const string& anXmlFile)
{
	CU::VectorOnStack<CardData*, DECK_MAX_SIZE> cardDataList = CardFactory::GetInstance().GetDeck(anXmlFile);

	myDeck.Clear();

	CU::Matrix44<float> cardOrientation = CU::Matrix44<float>::CreateRotateAroundY(PI);
	for (int i = 0; i < cardDataList.Size(); ++i)
	{
		myDeck.Add(Card());
		myDeck[i].LoadCard(cardDataList[i]);
		myDeck[i].SetOrientation(cardOrientation);
		myDeck[i].SetPosition(Vector3<float>(i * 2.f, 0, 0));
	}

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

