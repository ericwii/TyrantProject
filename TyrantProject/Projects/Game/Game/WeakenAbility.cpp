#include "stdafx.h"
#include "WeakenAbility.h"


WeakenAbility::WeakenAbility(const string & aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/weakenIcon.png";
	myAbilityType = eAbilityTypes::eWeaken;
}

WeakenAbility::~WeakenAbility()
{
}

void WeakenAbility::OnPreCombat(Card * aCard)
{
	if (aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTargetOffCoolDown(aCard->GetOwner()->GetOpponent()->GetAssaultCards());

			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargetsOffCoolDown(aCard->GetOwner()->GetOpponent()->GetAssaultCards());

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets);
			}
		}
	}
}

void WeakenAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Weaken(myNumber);
	}
}
