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
			myHasUpdatedCommander = UpdateAbilities(anActivePlayer.myComander, eAbilityMethod::eCalculateAttack);
		}
		else if (myCurrentStructureCardIndex < anActivePlayer.myStructureCards.Size())
		{
			if (UpdateAbilities(anActivePlayer.myStructureCards[myCurrentStructureCardIndex], eAbilityMethod::ePreCombat) == true)
			{
				++myCurrentStructureCardIndex;
			}
		}
		else if (myCurrentAssaultCardIndex < anActivePlayer.myAssaultCards.Size())
		{
			if (UpdateAbilities(anActivePlayer.myAssaultCards[myCurrentAssaultCardIndex], eAbilityMethod::ePreCombat) == true)
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
	//Vector2<float> size(2.f, 2.f);

	switch (myCombatState)
	{
		case (eCombatState::Setup):
		{
			if (myCurrentAssaultCardIndex < anAttacker.myAssaultCards.Size())
			{
				if (CombatSetup(anAttacker, aDefender) == true)
				{
					myCombatState = eCombatState::CalculateAttack;
				}
				else
				{
					++myCurrentAssaultCardIndex;
				}
			}
			else
			{
				return true;
			}
			break;
		}
		case (eCombatState::CalculateAttack):
		{
			if (CombatCalculations(anAttacker) == true)
			{
				myCombatState = eCombatState::DoAtack;
			}
			break;
		}
		case (eCombatState::DoAtack):
		{
			if (CombatAttack() == true)
			{
				myCombatState = eCombatState::Setup;
				++myCurrentAssaultCardIndex;

				if (anAttacker.CommanderIsDead() || aDefender.CommanderIsDead())
				{
					return true;
				}
			}
			break;
		}
		default:
		{
			myCombatState = eCombatState::Setup;
			myCurrentAssaultCardIndex = 0;
			return true;
		}
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
			myHasUpdatedCommander = UpdateAbilities(anActivePlayer.myComander, eAbilityMethod::eCleanup);
		}
		else if (myCurrentStructureCardIndex < anActivePlayer.myStructureCards.Size())
		{
			if (UpdateAbilities(anActivePlayer.myStructureCards[myCurrentStructureCardIndex], eAbilityMethod::eCleanup) == true)
			{
				++myCurrentStructureCardIndex;
			}
		}
		else if (myCurrentAssaultCardIndex < anActivePlayer.myAssaultCards.Size())
		{
			if (UpdateAbilities(anActivePlayer.myAssaultCards[myCurrentAssaultCardIndex], eAbilityMethod::eCleanup) == true)
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

CardGameManager::CardGameManager() : 
	myCurrentAssaultCardIndex(0), myCurrentStructureCardIndex(0), myCurrentAbilityIndex(0), myCurrentAttackIndex(0),
	myCombatState(eCombatState::Setup), myPhaseUpdateDone(false)
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

bool CardGameManager::UpdateAbilities(Card* aCard, eAbilityMethod aMethod)
{
	myCurrentAbilities = aCard->GetAbilities();

	if (myCurrentAbilityIndex < myCurrentAbilities.Size() && myCurrentAbilities[myCurrentAbilityIndex] != nullptr)
	{
		switch (aMethod)
		{
			case (eAbilityMethod::eCleanup):
			{
				myCurrentAbilities[myCurrentAbilityIndex]->OnCleanUp(aCard);
				break;
			}
			case (eAbilityMethod::ePreCombat):
			{
				myCurrentAbilities[myCurrentAbilityIndex]->OnPreCombat(aCard);
				break;
			}
			case (eAbilityMethod::eCalculateAttack):
			{
				myCurrentAttackData.attacker = aCard;
				myCurrentAbilities[myCurrentAbilityIndex]->OnCalculateAttack(myCurrentAttackData);
				break;
			}
			default:
			{
				break;
			}
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



//Combat

bool CardGameManager::CombatSetup(Player& anAttacker, Player& aDefender)
{
	if (anAttacker.myAssaultCards[myCurrentAssaultCardIndex]->GetCooldown() < 1 && anAttacker.myAssaultCards[myCurrentAssaultCardIndex]->GetAttack() > 0)
	{
		myCurrentAttackData.extraTargets[0] = nullptr;
		myCurrentAttackData.extraTargets[1] = nullptr;
		myCurrentAttackData.amountOfAttacks = 1;
		myCurrentAttackData.attackAnimation = &attackAnimation;
		myCurrentAttackData.attacker = anAttacker.myAssaultCards[myCurrentAssaultCardIndex];

		if (myCurrentAssaultCardIndex < aDefender.myAssaultCards.Size() && !aDefender.myAssaultCards[myCurrentAssaultCardIndex]->IsDying())
		{
			myCurrentAttackData.mainTarget = aDefender.myAssaultCards[myCurrentAssaultCardIndex];
		}
		else
		{
			myCurrentAttackData.mainTarget = aDefender.GetCommander();
		}

		myCurrentAbilities = myCurrentAttackData.attacker->GetAbilities();
		return true;
	}
	return false;
}

bool CardGameManager::CombatCalculations(Player& aDefender)
{
	if (AnimationManager::IsEmpty() && AbilityStack::IsEmpty())
	{
		if (myCurrentAbilityIndex < myCurrentAbilities.Size() && myCurrentAbilities[myCurrentAbilityIndex] != nullptr)
		{
			myCurrentAbilities[myCurrentAbilityIndex]->OnCalculateAttack(myCurrentAttackData);
			++myCurrentAbilityIndex;
		}
		else
		{
			if (myCurrentAttackData.mainTarget == aDefender.GetCommander())
			{
				CU::GrowingArray<Card*>& structures = aDefender.GetStructureCards();
				for (int i = 0; i < structures.Size(); ++i)
				{
					myCurrentAbilities = structures[i]->GetAbilities();
					for (int j = 0; j < myCurrentAbilities.Size(); ++j)
					{
						if (myCurrentAbilities[i] != nullptr)
						{
							myCurrentAbilities[j]->OnCommanderAttack(myCurrentAttackData.mainTarget, structures[i]);
						}
					}
				}
			}
			myCurrentAbilityIndex = 0;
			return true;
		}
	}
	return false;
}

bool CardGameManager::CombatAttack()
{
	if (myCurrentAttackIndex < myCurrentAttackData.amountOfAttacks)
	{
		if (AnimationManager::IsEmpty() && AbilityStack::IsEmpty())
		{
			if (myCurrentAttackData.attacker->CanAttack())
			{
				if (myCurrentAttackData.attacker->GetOwner()->myPlayerType == ePlayerType::User)
				{
					AnimationManager::AddAnimation(*myCurrentAttackData.attackAnimation, myCurrentAttackData.attacker->GetPosition(), Vector2<float>(2.f, 2.f));
				}
				else
				{
					AnimationManager::AddAnimation(*myCurrentAttackData.attackAnimation, myCurrentAttackData.attacker->GetPosition(), Vector2<float>(2.f, 2.f), PI);
				}

				if (myCurrentAttackData.extraTargets[0] != nullptr)
				{
					AttackCard(myCurrentAttackData.attacker, myCurrentAttackData.extraTargets[0]);
				}

				AttackCard(myCurrentAttackData.attacker, myCurrentAttackData.mainTarget);

				if (!myCurrentAttackData.mainTarget->GetOwner()->CommanderIsDead())
				{
					if (myCurrentAttackData.extraTargets[1] != nullptr)
					{
						AttackCard(myCurrentAttackData.attacker, myCurrentAttackData.extraTargets[1]);
					}
					++myCurrentAttackIndex;
				}
				else
				{
					return true;
				}
			}
			else
			{
				myCurrentAttackIndex = myCurrentAttackData.amountOfAttacks;
			}
		}
		return false;
	}

	myCurrentAttackIndex = 0;
	return true;
}

void CardGameManager::AttackCard(Card* anAttacker, Card* aDefender)
{
	char finalDamage = anAttacker->GetAttack();

	myCurrentAbilities = anAttacker->GetAbilities();
	for (int i = 0; i < myCurrentAbilities.Size(); ++i)
	{
		myCurrentAbilities[i]->OnAttack(aDefender, finalDamage);
	}

	myCurrentAbilities = aDefender->GetAbilities();
	for (int i = 0; i < myCurrentAbilities.Size(); ++i)
	{
		myCurrentAbilities[i]->OnAttacked(aDefender, finalDamage, anAttacker);
	}

	if (finalDamage > 0)
	{
		myCurrentAbilities = anAttacker->GetAbilities();
		for (int i = 0; i < myCurrentAbilities.Size(); ++i)
		{
			myCurrentAbilities[i]->OnDamageDealt(anAttacker, aDefender, finalDamage);
		}
		aDefender->TakeDamage(finalDamage);
	}
}
