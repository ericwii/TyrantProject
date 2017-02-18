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
	myPlayerUser.Init("Data/Xml files/starterDeck.xml", ePlayerType::User);
	myPlayerOpponent.Init("Data/Xml files/starterDeck.xml", ePlayerType::AI_Opponent);

	Model* backgroundModel = ModelLoader::LoadRectangle(Vector2<float>(2.f, 2.f), eEffectType::Sprite, "Data/Textures/Field/playingField.png");
	myBackground.Init(backgroundModel);

	Model* deckGuiModel = ModelLoader::LoadRectangle(Vector2<float>(0.5f, 2.f), eEffectType::Sprite, "Data/Textures/Field/deckGUI2.png");
	myDeckGUI.Init(deckGuiModel);
	myDeckGUI.SetPosition(Vector3<float>(-0.75f, -0.01f, 0));

	myCurrentPhase = Upkeep;
	usersTurn = true;
}

void CardGameState::Update()
{
	if (usersTurn)
	{
		if (myPlayerUser.Update(myCurrentPhase) == false)
		{
			if (myCurrentPhase != eGamePhase::Cleanup)
			{
				myCurrentPhase = eGamePhase(myCurrentPhase + 1);
			}
			else
			{
				myCurrentPhase = Upkeep;
				usersTurn = false;
			}
		}
	}
	else
	{
		if (myPlayerOpponent.Update(myCurrentPhase) == false)
		{
			if (myCurrentPhase != eGamePhase::Cleanup)
			{
				myCurrentPhase = eGamePhase(myCurrentPhase + 1);
			}
			else
			{
				myCurrentPhase = Upkeep;
				usersTurn = true;
			}
		}
	}
}

void CardGameState::Render()
{
	myBackground.Render();
	myDeckGUI.Render();

	myPlayerUser.Render();
	myPlayerOpponent.Render();
}

void CardGameState::OnExit()
{

}