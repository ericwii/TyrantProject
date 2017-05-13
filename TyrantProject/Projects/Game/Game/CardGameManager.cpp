#include "stdafx.h"
#include "CardGameManager.h"
#include "Player.h"
#include "Card.h"
#include "AbilityBase.h"

CardGameManager* CardGameManager::instance = new CardGameManager();
AnimationData attackAnimation
{
	"Data/Textures/Animations/attackAnimation.png",
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
		instance->myChoosenCard = nullptr;
		instance->myCurrentStructureCardIndex = 0;
		instance->myCurrentAssaultCardIndex = 0;
		instance->myCurrentAbilityIndex = 0;
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
	if (anActivePlayer.myHand.HasCards() == false)
	{
		return true;
	}

	if (anActivePlayer.ChooseCardToPlay(myChoosenCard) == true)
	{
		anActivePlayer.PlayCard(myChoosenCard);
		return true;
	}

	return false;
}

bool CardGameManager::PreCombat(Player& anActivePlayer)
{
	if (AnimationManager::IsEmpty() && AbilityStack::IsEmpty())
	{
		Card* currentCard = nullptr;
		CU::VectorOnStack<AbilityBase*,3> currentAbilities;
		if (myCurrentStructureCardIndex < anActivePlayer.myStructureCards.Size())
		{
			currentCard = anActivePlayer.myStructureCards[myCurrentStructureCardIndex];
			currentAbilities = currentCard->GetAbilities();

			if (myCurrentAbilityIndex < currentAbilities.Size() && currentAbilities[myCurrentAbilityIndex] != nullptr)
			{
				currentAbilities[myCurrentAbilityIndex]->OnPreCombat(currentCard);
				++myCurrentAbilityIndex;
			}
			else
			{
				++myCurrentStructureCardIndex;
				myCurrentAbilityIndex = 0;
			}
		}
		else if (myCurrentAssaultCardIndex < anActivePlayer.myAssaultCards.Size())
		{
			currentCard = anActivePlayer.myAssaultCards[myCurrentAssaultCardIndex];
			currentAbilities = currentCard->GetAbilities();

			if (myCurrentAbilityIndex < currentAbilities.Size() && currentAbilities[myCurrentAbilityIndex] != nullptr)
			{
				currentAbilities[myCurrentAbilityIndex]->OnPreCombat(currentCard);
				++myCurrentAbilityIndex;
			}
			else
			{
				++myCurrentAssaultCardIndex;
				myCurrentAbilityIndex = 0;
			}
		}
		else
		{
			return true;
		}
	}

	return false;
}

bool CardGameManager::Combat(Player& anAttacker, Player& aDefender)
{
	Vector2<float> size(2.f, 2.f);

	if (myCurrentAssaultCardIndex >= anAttacker.myAssaultCards.Size())
	{
		return true;
	}

	if (AnimationManager::IsEmpty() && AbilityStack::IsEmpty())
	{
		Card* currentCard = anAttacker.myAssaultCards[myCurrentAssaultCardIndex];
		if (currentCard->GetCooldown() < 1)
		{
			Card* defendingCard;
			if (aDefender.myAssaultCards.Size() > myCurrentAssaultCardIndex && !aDefender.myAssaultCards[myCurrentAssaultCardIndex]->IsDying())
			{
				defendingCard = aDefender.myAssaultCards[myCurrentAssaultCardIndex];
			}
			else
			{
				defendingCard = aDefender.myComander;
			}

			char finalDamage = currentCard->GetAttack();
			defendingCard->OnAttacked(finalDamage);
			if (finalDamage > 0)
			{
				Vector3<float> position = anAttacker.myAssaultCards[myCurrentAssaultCardIndex]->GetOrientation().GetPosition();
				if (position.y < 0)
				{
					AnimationManager::AddAnimation(attackAnimation, position, size);
				}
				else
				{
					AnimationManager::AddAnimation(attackAnimation, position, size, PI);
				}

				defendingCard->TakeDamage(finalDamage);
				if (aDefender.CommanderIsDead())
				{
					myCurrentAssaultCardIndex = anAttacker.myAssaultCards.Size();
					CleanUp(anAttacker, aDefender);
				}
			}
		}

		++myCurrentAssaultCardIndex;
	}

	return false;
}

void CardGameManager::CleanUp(Player& anActivePlayer, Player& anOpponentPlayer)
{
	for (int i = 0; i < anActivePlayer.myAssaultCards.Size(); ++i)
	{
		if (anActivePlayer.myAssaultCards[i]->IsDying())
		{
			anActivePlayer.myAssaultCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
	}

	for (int i = 0; i < anOpponentPlayer.myAssaultCards.Size(); ++i)
	{
		if (anOpponentPlayer.myAssaultCards[i]->IsDying())
		{
			anOpponentPlayer.myAssaultCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
	}

	for (int i = 0; i < anActivePlayer.myStructureCards.Size(); ++i)
	{
		if (anActivePlayer.myStructureCards[i]->IsDying())
		{
			anActivePlayer.myStructureCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
	}

	for (int i = 0; i < anOpponentPlayer.myStructureCards.Size(); ++i)
	{
		if (anOpponentPlayer.myStructureCards[i]->IsDying())
		{
			anOpponentPlayer.myStructureCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
	}

	anActivePlayer.RepositionPlayedCards();
	anOpponentPlayer.RepositionPlayedCards();


	CU::VectorOnStack<AbilityBase*, 3> currentAbilities = anActivePlayer.GetCommander()->GetAbilities();
	for (short i = 0; i < currentAbilities.Size(); i++)
	{
		currentAbilities[i]->OnCleanUp(anActivePlayer.GetCommander());
	}

	for (short i = 0; i < anActivePlayer.GetStructureCards().Size(); i++)
	{
		currentAbilities = anActivePlayer.GetStructureCards()[i]->GetAbilities();
		for (short j = 0; j < currentAbilities.Size(); j++)
		{
			currentAbilities[j]->OnCleanUp(anActivePlayer.GetStructureCards()[i]);
		}
	}

	for (short i = 0; i < anActivePlayer.GetAssaultCards().Size(); i++)
	{
		currentAbilities = anActivePlayer.GetAssaultCards()[i]->GetAbilities();
		for (short j = 0; j < currentAbilities.Size(); j++)
		{
			currentAbilities[j]->OnCleanUp(anActivePlayer.GetAssaultCards()[i]);
		}
	}
}




//Private Methods

CardGameManager::CardGameManager() : myCurrentAssaultCardIndex(0), myCurrentStructureCardIndex(0), myCurrentAbilityIndex(0), myPhaseUpdateDone(false)
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

	return actions < 1 && AnimationManager::IsEmpty() && AbilityStack::IsEmpty();
}
