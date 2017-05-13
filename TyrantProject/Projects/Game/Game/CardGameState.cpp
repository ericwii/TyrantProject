#include "stdafx.h"
#include "CardGameState.h"
#include "CardGameTextManager.h"



CardGameState::CardGameState()
{

}

CardGameState::~CardGameState()
{

}


void CardGameState::OnEnter()
{
	myPlayerUser.Init("Data/Xml files/starterDeck.xml", ePlayerType::User, &myPlayerOpponent);
	myPlayerOpponent.Init("Data/Xml files/starterDeck.xml", ePlayerType::AI_Opponent, &myPlayerUser);

	Model* backgroundModel = ModelLoader::LoadRectangle(Vector2<float>(2.f, 2.f), eEffectType::Sprite, "Data/Textures/Field/playingField.png");
	myBackground.Init(backgroundModel);

	Model* deckGuiModel = ModelLoader::LoadRectangle(Vector2<float>(0.5f, 2.f), eEffectType::Sprite, "Data/Textures/Field/deckGUI2.png");
	myDeckGUI.Init(deckGuiModel);
	myDeckGUI.SetPosition(Vector3<float>(-0.75f, -0.01f, 0));

	TextFont* font = Engine::GetInstance()->GetFontContainer().GetFont("Data/Fonts/debugFont.dds", eEffectType::Text3D);
	string text = "Turn:0";
	myTurnCounterText.Init(font);
	myTurnCounterText.SetPosition(Vector3<float>(-1.25f, 0.1f, -4.f));
	myTurnCounterText.SetText(text);
	myTurnCount = 0;

	myCurrentPhase = Upkeep;
	myUsersTurn = true;
	myGameIsOver = false;
}


void CardGameState::Update()
{
	if (myGameIsOver == false)
	{
		if (myUsersTurn == true)
		{
			if (CardGameManager::Update(myCurrentPhase, myPlayerUser, myPlayerOpponent) == true)
			{
				ChangePhase();
			}
		}
		else
		{
			if (CardGameManager::Update(myCurrentPhase, myPlayerOpponent, myPlayerUser) == true)
			{
				ChangePhase();
			}

		}
	}

	float deltaTime = Time::DeltaTime();
	AnimationManager::Update(deltaTime);
	CardGameTextManager::Update(deltaTime);
	AbilityStack::Update(deltaTime);
}

void CardGameState::Render()
{
	myBackground.Render();
	myDeckGUI.Render();
	myTurnCounterText.Render();

	myPlayerOpponent.Render();
	myPlayerUser.Render();

	AnimationManager::Render();
	CardGameTextManager::Render();

	if (myGameIsOver)
	{
		if (myPlayerOpponent.CommanderIsDead())
		{
			Engine::GetInstance()->RenderDebugText("You Win", Vector2<float>(-0.07f,-0.03f));
		}
		else
		{
			Engine::GetInstance()->RenderDebugText("You Lose", Vector2<float>(-0.1f, -0.03f));
		}
	}
}

void CardGameState::OnExit()
{

}



//Private Methods

void CardGameState::ChangePhase()
{
	if (myPlayerUser.CommanderIsDead() || myPlayerOpponent.CommanderIsDead())
	{
		myGameIsOver = true;
		return;
	}

	if (myCurrentPhase == eGamePhase::Cleanup)
	{
		myCurrentPhase = eGamePhase::Upkeep;
		myUsersTurn = !myUsersTurn;

		++myTurnCount;
		string turnText("Turn:");
		turnText += myTurnCount;
		myTurnCounterText.SetText(turnText);
	}
	else
	{
		myCurrentPhase = eGamePhase(myCurrentPhase + 1);
	}
}