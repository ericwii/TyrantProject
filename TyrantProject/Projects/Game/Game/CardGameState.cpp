#include "stdafx.h"
#include "CardGameState.h"
#include "CardGameTextManager.h"
#include "CardGameCameraManager.h"
#include "GUIManager.h"



CardGameState::CardGameState() : myRenderDebugHitboxes(false)
{

}

CardGameState::~CardGameState()
{

}


void CardGameState::OnEnter()
{
	myPlayerUser.Init("Data/Xml files/PlayerDeck.xml", ePlayerType::User, &myPlayerOpponent);
	myPlayerOpponent.Init("Data/Xml files/OpponentDeck.xml", ePlayerType::AI_Opponent, &myPlayerUser);

	Model* backgroundModel = ModelLoader::LoadRectangle(Vector2<float>(2.f, 2.f), eEffectType::SpriteWrap, "Data/Textures/Field/playingField.png");
	myBackground.Init(backgroundModel);

	Model* deckGuiModel = ModelLoader::LoadRectangle(Vector2<float>(3.8f, 10.f), eEffectType::Textured, "Data/Textures/Field/deckGUI2.png");
	myDeckGUI.Init(deckGuiModel);
	myDeckGUI.SetPosition(Vector3<float>(-5.62f, 0, 0));

	TextFont* font = Engine::GetInstance()->GetFontContainer().GetFont("Data/Fonts/debugFont.dds", eEffectType::Text3D);
	string text = "Turn:0";
	myTurnCounterText.Init(font);
	myTurnCounterText.SetPosition(Vector3<float>(-6.25f, 0.52f, 0));
	myTurnCounterText.SetCharacterScale(Vector2<float>(5.f, 5.f));
	myTurnCounterText.SetText(text);
	myTurnCount = 0;

	myCurrentPhase = Upkeep;
	myUsersTurn = true;
	myGameIsOver = false;

	AbilityStack::Init();
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
	CardGameCameraManager::Update(deltaTime);
	AbilityStack::Update(deltaTime);
	GUIManager::Update(deltaTime);

	if (InputManager::Keyboard.WasKeyJustPressed(DIK_F5))
	{
		myRenderDebugHitboxes = !myRenderDebugHitboxes;
	}
}

void CardGameState::Render()
{
	myBackground.Render();
	myDeckGUI.Render();
	myTurnCounterText.Render();
	myPlayerOpponent.Render();
	myPlayerUser.Render();

	AbilityStack::Render();
	AnimationManager::Render();
	CardGameTextManager::Render();
	GUIManager::Render();

	if (myRenderDebugHitboxes)
	{
		GUIManager::RenderDebugHitboxes();
	}

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
		if (myTurnCount > 50)
		{
			myGameIsOver = true;
		}
		else
		{
			string turnText("Turn:");
			turnText += myTurnCount;
			myTurnCounterText.SetText(turnText);
		}
	}
	else
	{
		myCurrentPhase = eGamePhase(myCurrentPhase + 1);
		CardGameCameraManager::SetLerpTarget(Vector3<float>());
	}
}