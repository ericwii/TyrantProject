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
				instance->myPhaseUpdateDone = instance->CleanUp(anActivePlayer, aOtherPlayer);
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
		instance->myHasUpdatedCommander = false;
		instance->myHasRemovedDeadCards = false;
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

		CU::VectorOnStack<AbilityBase*, 3> currentAbilities;

		currentAbilities = myChoosenCard->GetAbilities();

		for (char j = 0; j < currentAbilities.Size(); j++)
		{
			currentAbilities[j]->OnPlay(myChoosenCard);
		}

		return true;
	}

	return false;
}

bool CardGameManager::PreCombat(Player& anActivePlayer)
{
	if (AnimationManager::IsEmpty() && AbilityStack::IsEmpty())
	{
		if (myHasUpdatedCommander == false)
		{
			myHasUpdatedCommander = UpdateAbilities(anActivePlayer.myComander);
		}
		else if (myCurrentStructureCardIndex < anActivePlayer.myStructureCards.Size())
		{
			if (UpdateAbilities(anActivePlayer.myStructureCards[myCurrentStructureCardIndex]) == true)
			{
				++myCurrentStructureCardIndex;
			}
		}
		else if (myCurrentAssaultCardIndex < anActivePlayer.myAssaultCards.Size())
		{
			if (UpdateAbilities(anActivePlayer.myAssaultCards[myCurrentAssaultCardIndex]) == true)
			{
				++myCurrentAssaultCardIndex;
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
	CU::VectorOnStack<AbilityBase*, 3> currentAbilities;

	if (myCurrentAssaultCardIndex >= anAttacker.myAssaultCards.Size())
	{
		return true;
	}

	if (AnimationManager::IsEmpty() && AbilityStack::IsEmpty())
	{
		Card* currentCard = anAttacker.myAssaultCards[myCurrentAssaultCardIndex];
		Card* defendingCard = nullptr;
		char finalDamage = currentCard->GetAttack();

		if (currentCard->GetCooldown() < 1)
		{
			currentAbilities = currentCard->GetAbilities();
			for (int i = 0; i < currentAbilities.Size(); i++)
			{
				currentAbilities[i]->OnBeforeAttack(currentCard, defendingCard, finalDamage);
			}
		}

		if (currentCard->GetCooldown() < 1 && currentCard->GetAttack() > 0)
		{
			if (aDefender.myAssaultCards.Size() > myCurrentAssaultCardIndex && !aDefender.myAssaultCards[myCurrentAssaultCardIndex]->IsDying())
			{
				defendingCard = aDefender.myAssaultCards[myCurrentAssaultCardIndex];
			}
			else
			{
				defendingCard = aDefender.myComander;
			}

			
			if (defendingCard == aDefender.myComander)
			{
				for (short i = 0; i < aDefender.GetStructureCards().Size(); i++)
				{
					currentAbilities = aDefender.GetStructureCards()[i]->GetAbilities();
					for (char j = 0; j < currentAbilities.Size(); j++)
					{
						currentAbilities[j]->OnCommanderAttack(defendingCard, aDefender.GetStructureCards()[i]);
					}

					if (defendingCard != aDefender.myComander)
					{
						break;
					}
				}
			}




			defendingCard->OnAttacked(defendingCard ,finalDamage, anAttacker.myAssaultCards[myCurrentAssaultCardIndex]);

			Vector3<float> position = anAttacker.myAssaultCards[myCurrentAssaultCardIndex]->GetOrientation().GetPosition();
			if (position.y < 0)
			{
				AnimationManager::AddAnimation(attackAnimation, position, size);
			}
			else
			{
				AnimationManager::AddAnimation(attackAnimation, position, size, PI);
			}


			if (finalDamage > 0)
			{

				defendingCard->TakeDamage(finalDamage);
				anAttacker.myAssaultCards[myCurrentAssaultCardIndex]->OnDamageDealt(anAttacker.myAssaultCards[myCurrentAssaultCardIndex], defendingCard, finalDamage);

				if (defendingCard->IsDying() == true)
				{
					anAttacker.myAssaultCards[myCurrentAssaultCardIndex]->OnKill(anAttacker.myAssaultCards[myCurrentAssaultCardIndex],defendingCard);
				}

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

bool CardGameManager::CleanUp(Player& anActivePlayer, Player& anOpponentPlayer)
{
	if (myHasRemovedDeadCards == false)
	{
		RemoveDeadCards(anActivePlayer, anOpponentPlayer);
		anActivePlayer.RepositionPlayedCards();
		anOpponentPlayer.RepositionPlayedCards();
		myHasRemovedDeadCards = true;
	}

	if (AnimationManager::IsEmpty() && AbilityStack::IsEmpty())
	{
		if (myHasUpdatedCommander == false)
		{
			myHasUpdatedCommander = UpdateAbilities(anActivePlayer.myComander, true);
		}
		else if (myCurrentStructureCardIndex < anActivePlayer.myStructureCards.Size())
		{
			if (UpdateAbilities(anActivePlayer.myStructureCards[myCurrentStructureCardIndex], true) == true)
			{
				++myCurrentStructureCardIndex;
			}
		}
		else if (myCurrentAssaultCardIndex < anActivePlayer.myAssaultCards.Size())
		{
			if (UpdateAbilities(anActivePlayer.myAssaultCards[myCurrentAssaultCardIndex], true) == true)
			{
				++myCurrentAssaultCardIndex;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
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

void CardGameManager::RemoveDeadCards(Player& anActivePlayer, Player& anOpponentPlayer)
{
	for (int i = 0; i < anActivePlayer.myAssaultCards.Size(); ++i)
	{
		if (anActivePlayer.myAssaultCards[i]->IsDying())
		{
			anActivePlayer.myAssaultCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
		else
		{
			anActivePlayer.myAssaultCards[i]->CleanUp();
		}
	}

	for (int i = 0; i < anOpponentPlayer.myAssaultCards.Size(); ++i)
	{
		if (anOpponentPlayer.myAssaultCards[i]->IsDying())
		{
			anOpponentPlayer.myAssaultCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
		else
		{
			//anOpponentPlayer.myAssaultCards[i]->CleanUp();
		}
	}

	for (int i = 0; i < anActivePlayer.myStructureCards.Size(); ++i)
	{
		if (anActivePlayer.myStructureCards[i]->IsDying())
		{
			anActivePlayer.myStructureCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
		else
		{
			anActivePlayer.myStructureCards[i]->CleanUp();
		}
	}

	for (int i = 0; i < anOpponentPlayer.myStructureCards.Size(); ++i)
	{
		if (anOpponentPlayer.myStructureCards[i]->IsDying())
		{
			anOpponentPlayer.myStructureCards.RemoveNonCyclicAtIndex(i);
			--i;
		}
		else
		{
			//anOpponentPlayer.myStructureCards[i]->CleanUp();
		}
	}
}

bool CardGameManager::UpdateAbilities(Card* aCard, bool cleanUp)
{
	myCurrentAbilities = aCard->GetAbilities();

	if (myCurrentAbilityIndex < myCurrentAbilities.Size() && myCurrentAbilities[myCurrentAbilityIndex] != nullptr)
	{
		if (cleanUp)
		{
			myCurrentAbilities[myCurrentAbilityIndex]->OnCleanUp(aCard);
		}
		else
		{
			myCurrentAbilities[myCurrentAbilityIndex]->OnPreCombat(aCard);
		}
		++myCurrentAbilityIndex;
	}
	else
	{
		myCurrentAbilityIndex = 0;
		return true;
	}
	return false;
}
