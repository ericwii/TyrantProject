#include "stdafx.h"
#include "CardGameManager.h"
#include "Player.h"
#include "AnimationStack.h"

CardGameManager* CardGameManager::instance = new CardGameManager();
AnimationData attackAnimation
{
	"Data/Textures/attackAnimation.png",
		10,
		2,
		30.f,
		false
};




bool CardGameManager::Update(eGamePhase aCurrentPhase, Player& anActivePlayer, Player& aOtherPlayer)
{
	if (instance->myPhaseUpdateDone == false)
	{
		switch (aCurrentPhase)
		{
			case(eGamePhase::Upkeep) :
			{
				instance->Upkeep(anActivePlayer);
				instance->myPhaseUpdateDone = true;
				break;
			}
			case(eGamePhase::Play) :
			{
				instance->myPhaseUpdateDone = instance->PlayCard(anActivePlayer);
				break;
			}
			case(eGamePhase::PreCombat) :
			{
				instance->myPhaseUpdateDone = instance->PreCombat(anActivePlayer);
				break;
			}
			case(eGamePhase::Combat) :
			{
				instance->myPhaseUpdateDone = instance->Combat(anActivePlayer, aOtherPlayer);
				break;
			}
			case(eGamePhase::Cleanup) :
			{
				instance->CleanUp(anActivePlayer, aOtherPlayer);
				instance->myPhaseUpdateDone = true;
				break;
			}
			default:
			{
				return true;
			}
		}
	}

	if (instance->AllActionsDone(anActivePlayer, aOtherPlayer) == true && instance->myPhaseUpdateDone)
	{
		instance->myChoosenCardIndex = -1;
		instance->myCurrentAttackerIndex = 0;
		instance->myPhaseUpdateDone = false;
		return true;
	}
	return false;
}

void CardGameManager::Upkeep(Player& anActivePlayer)
{
	for (int i = 0; i < anActivePlayer.myAssaultCards.Size(); ++i)
	{
		anActivePlayer.myAssaultCards[i]->LowerCooldown();
	}
	for (int i = 0; i < anActivePlayer.myStructureCards.Size(); ++i)
	{
		anActivePlayer.myStructureCards[i]->LowerCooldown();
	}
}

bool CardGameManager::PlayCard(Player& anActivePlayer)
{
	if (anActivePlayer.myDeckCards.Size() == 0)
	{
		return true;
	}

	myChoosenCardIndex = anActivePlayer.ChooseCardToPlay();

	if (myChoosenCardIndex >= 0)
	{
		Card* cardToPlay = anActivePlayer.myDeckCards[myChoosenCardIndex];
		anActivePlayer.PlayCard(cardToPlay);
		return true;
	}

	return false;
}

bool CardGameManager::PreCombat(Player& anActivePlayer)
{
	anActivePlayer;
	return true;
}

bool CardGameManager::Combat(Player& anAttacker, Player& aDefender)
{
	Vector2<float> size(2.f, 2.f);

	if (myCurrentAttackerIndex >= anAttacker.myAssaultCards.Size())
	{
		return true;
	}

	if (AnimationStack::IsEmpty())
	{
		Card* currentCard = anAttacker.myAssaultCards[myCurrentAttackerIndex];
		if (currentCard->GetCooldown() < 1)
		{
			Vector3<float> position = anAttacker.myAssaultCards[myCurrentAttackerIndex]->GetOrientation().GetPosition();

			if (position.y < 0)
			{
				AnimationStack::AddAnimation(attackAnimation, position, size);
			}
			else
			{
				AnimationStack::AddAnimation(attackAnimation, position, size, PI);
			}

			if (aDefender.myAssaultCards.Size() > myCurrentAttackerIndex)
			{
				aDefender.myAssaultCards[myCurrentAttackerIndex]->TakeDamage(currentCard->GetAttack());
			}
			else
			{
				aDefender.myComander->TakeDamage(currentCard->GetAttack());

				if (aDefender.CommanderIsDead())
				{
					myCurrentAttackerIndex = anAttacker.myAssaultCards.Size();
					CleanUp(anAttacker, aDefender);
				}
			}
		}

		++myCurrentAttackerIndex;
	}

	return false;
}

void CardGameManager::CleanUp(Player& anActivePlayer, Player& anOpponentPlayer)
{
	for (int i = 0; i < anActivePlayer.myAssaultCards.Size(); ++i)
	{
		if (anActivePlayer.myAssaultCards[i]->IsDead())
		{
			anActivePlayer.myAssaultCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
	}

	for (int i = 0; i < anOpponentPlayer.myAssaultCards.Size(); ++i)
	{
		if (anOpponentPlayer.myAssaultCards[i]->IsDead())
		{
			anOpponentPlayer.myAssaultCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
	}

	anActivePlayer.RepositionPlayedCards();
	anOpponentPlayer.RepositionPlayedCards();
}




//Private Methods

CardGameManager::CardGameManager() : myChoosenCardIndex(-1), myCurrentAttackerIndex(0), myPhaseUpdateDone(false)
{
}

CardGameManager::~CardGameManager()
{
}


int CardGameManager::UpdateCards(Player& aPlayer)
{
	float deltaTime = Time::DeltaTime();

	int updatingCards = 0;
	Card* currentCard;

	for (int i = 0; i < aPlayer.myAssaultCards.Size(); ++i)
	{
		currentCard = aPlayer.myAssaultCards[i];
		currentCard->Update(deltaTime);

		if ((!currentCard->IsDead() && currentCard->IsDying()) || currentCard->IsLerping())
		{
			++updatingCards;
		}
	}
	for (int i = 0; i < aPlayer.myStructureCards.Size(); ++i)
	{
		currentCard = aPlayer.myStructureCards[i];
		currentCard->Update(deltaTime);

		if ((!currentCard->IsDead() && currentCard->IsDying()) || currentCard->IsLerping())
		{
			++updatingCards;
		}
	}

	return updatingCards;
}

bool CardGameManager::AllActionsDone(Player& aPlayer, Player& aOtherPlayer)
{
	int actions = UpdateCards(aPlayer);
	actions += UpdateCards(aOtherPlayer);

	return actions < 1 && AnimationStack::IsEmpty();
}