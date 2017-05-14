#include "stdafx.h"
#include "AbilityBase.h"


AbilityBase::AbilityBase() : myNumber(0)
{
}

AbilityBase::AbilityBase(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : mySuffix(aSuffix), myNumber(aNumber), mySpecificFaction(aSpecificFaction)
{
	if (mySuffix == "all")
	{
		myTargets.Allocate(8);
	}
}

AbilityBase::~AbilityBase()
{
}




void AbilityBase::OnPlay(Card* aCard) { aCard; }
void AbilityBase::OnDeath(Card* aCard) { aCard; }
void AbilityBase::OnCombatDamaged(char someDamage, Card* aCard, Card* anAttacker) { someDamage; aCard; anAttacker; }
void AbilityBase::OnKill(Card* aCard) { aCard; }
void AbilityBase::OnPreCombat(Card* aCard) { aCard; }
void AbilityBase::OnCleanUp(Card * aCard) { aCard; }
void AbilityBase::OnTargeted(Card* aTarget) { aTarget; }
void AbilityBase::OnAttacked(char& someDamage, Card* anAttacker) { someDamage; anAttacker; }
void AbilityBase::OnCommanderAttack(Card*& aCurrentTarget, Card* aUser)
{
	aCurrentTarget;
	aUser;
}
void AbilityBase::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	someTargets;
}

const eAbilityTypes AbilityBase::GetAbilityType()
{
	return myAbilityType;
}

const char AbilityBase::GetNumber()
{
	return myNumber;
}


//Protected Methods

Card* AbilityBase::FindTarget(CU::GrowingArray<Card*>& cards)
{
	if (cards.Size() > 0)
	{
		int randomIndex = rand() % cards.Size();
		for (int searchCount = 0; searchCount < cards.Size(); ++searchCount)
		{
			if (!cards[randomIndex]->IsDying() && (mySpecificFaction == eCardFaction::Action || cards[randomIndex]->GetFaction() == mySpecificFaction))
			{
				return cards[randomIndex];
			}

			++randomIndex;
			randomIndex %= cards.Size();
		}
	}
	return nullptr;
}

Card* AbilityBase::FindTargetOffCoolDown(CU::GrowingArray<Card*>& cards)
{
	if (cards.Size() > 0)
	{
		int randomIndex = rand() % cards.Size();
		for (int searchCount = 0; searchCount < cards.Size(); ++searchCount)
		{
			if (!cards[randomIndex]->IsDying() && cards[randomIndex]->GetCooldown() < 1 && (mySpecificFaction == eCardFaction::Action || cards[randomIndex]->GetFaction() == mySpecificFaction))
			{
				return cards[randomIndex];
			}

			++randomIndex;
			randomIndex %= cards.Size();
		}
	}
	return nullptr;
}

CU::GrowingArray<Card*>& AbilityBase::FindAllTargets(CU::GrowingArray<Card*>& cards)
{
	myTargets.RemoveAll();

	Card* currentTarget;

	if (mySpecificFaction == eCardFaction::Action)
	{
		for (int i = cards.Size() - 1; i >= 0; --i)
		{
			currentTarget = cards[i];

			if (currentTarget != nullptr && !currentTarget->IsDying())
			{
				myTargets.Add(currentTarget);
			}
		}
	}
	else
	{
		for (int i = cards.Size() - 1; i >= 0; --i)
		{
			currentTarget = cards[i];

			if (currentTarget != nullptr && !currentTarget->IsDying() && currentTarget->GetFaction() == mySpecificFaction)
			{
				myTargets.Add(currentTarget);
			}
		}
	}

	return myTargets;
}

CU::GrowingArray<Card*>& AbilityBase::FindAllTargetsOffCoolDown(CU::GrowingArray<Card*>& cards)
{
	myTargets.RemoveAll();

	Card* currentTarget;

	if (mySpecificFaction == eCardFaction::Action)
	{
		for (int i = cards.Size() - 1; i >= 0; --i)
		{
			currentTarget = cards[i];

			if (currentTarget != nullptr && !currentTarget->IsDying() && currentTarget->GetCooldown() < 1)
			{
				myTargets.Add(currentTarget);
			}
		}
	}
	else
	{
		for (int i = cards.Size() - 1; i >= 0; --i)
		{
			currentTarget = cards[i];

			if (currentTarget != nullptr && !currentTarget->IsDying() && currentTarget->GetFaction() == mySpecificFaction && currentTarget->GetCooldown() < 1)
			{
				myTargets.Add(currentTarget);
			}
		}
	}

	return myTargets;
}
