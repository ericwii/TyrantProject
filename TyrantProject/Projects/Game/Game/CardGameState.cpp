#include "stdafx.h"
#include "CardGameState.h"
#include "AnimationStack.h"
#include "DamageTextManager.h"


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

	myCurrentPhase = Upkeep;
	usersTurn = true;
	myGameIsOver = false;
}


bool playerHasFinishedUpdate = false;
void CardGameState::Update()
{
	if (myGameIsOver == false)
	{
		if (playerHasFinishedUpdate == false)
		{
			if (usersTurn)
			{
				playerHasFinishedUpdate = !myPlayerUser.Update(myCurrentPhase);
			}
			else
			{
				playerHasFinishedUpdate = !myPlayerOpponent.Update(myCurrentPhase);
			}
			UpdateCards();
		}
		else if (AnimationStack::IsEmpty() && UpdateCards() == true)
		{
			playerHasFinishedUpdate = false;
			if (myCurrentPhase != eGamePhase::Cleanup)
			{
				myCurrentPhase = eGamePhase(myCurrentPhase + 1);
			}
			else
			{
				if (myPlayerUser.CommanderIsDead() || myPlayerOpponent.CommanderIsDead())
				{
					myGameIsOver = true;
				}
				else
				{
					myCurrentPhase = Upkeep;
					usersTurn = !usersTurn;
				}
			}
		}
	}

	float deltaTime = Time::DeltaTime();
	AnimationStack::Update(deltaTime);
	DamageTextManager::Update(deltaTime);
}

void CardGameState::Render()
{
	myBackground.Render();
	myDeckGUI.Render();

	myPlayerUser.Render();
	myPlayerOpponent.Render();

	AnimationStack::Render();
	DamageTextManager::Render();

	if (myGameIsOver)
	{
		if (myPlayerOpponent.CommanderIsDead())
		{
			Engine::GetInstance()->RenderDebugText("You Win", Vector2<float>(0.43f,0.47f));
		}
		else
		{
			Engine::GetInstance()->RenderDebugText("You Lose", Vector2<float>(0.4f, 0.47f));
		}
	}
}

void CardGameState::OnExit()
{

}



//Private Methods

bool CardGameState::UpdateCards()
{
	 CU::VectorOnStack<Card, 20>& userCards = myPlayerUser.GetOwnedCards();
	 CU::VectorOnStack<Card, 20>& opponentCards = myPlayerOpponent.GetOwnedCards();

	float deltaTime = Time::DeltaTime();

	for (int i = 0; i < userCards.Size(); ++i)
	{
		userCards[i].Update(deltaTime);
		if (userCards[i].IsDying())
		{
			return false;
		}
	}
	for (int i = 0; i < opponentCards.Size(); ++i)
	{
		opponentCards[i].Update(deltaTime);
		if (opponentCards[i].IsDying())
		{
			return false;
		}
	}

	return true;
}