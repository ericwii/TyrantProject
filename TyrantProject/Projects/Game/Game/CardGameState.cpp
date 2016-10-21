#include "stdafx.h"
#include "CardGameState.h"


CardGameState::CardGameState()
{

}

CardGameState::~CardGameState()
{

}


void CardGameState::OnEnter()
{
	myPlayerUser.InitDeck("Data/Xml files/starterDeck.xml");
	myPlayerOpponent.InitDeck("Data/Xml files/starterDeck.xml");
}

void CardGameState::Update()
{

}

void CardGameState::Render()
{
	myPlayerUser.Render();
}

void CardGameState::OnExit()
{

}