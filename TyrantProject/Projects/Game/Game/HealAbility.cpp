#include "stdafx.h"
#include "HealAbility.h"

Vector2<float> healAnimationSize(2.f, 2.f);
AnimationData healAnimation = AnimationData
(
	"Data/Textures/Animations/strikeAnimation.png",
	18,
	4,
	30.f,
	false
);


HealAbility::HealAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/healIcon.png";
}

HealAbility::~HealAbility()
{
}



void HealAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Heal(myNumber);
	}
}

void HealAbility::OnPreCombat(Card* aCard)
{
	if (aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards());
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target);
			}
		}
		else if (mySuffix == "all")
		{
			Card* currentTarget;
			CU::GrowingArray<Card*> targets = aCard->GetOwner()->GetAssaultCards();
			for (int i = targets.Size() - 1; i >= 0; --i)
			{
				currentTarget = targets[i];

				if (currentTarget == nullptr || currentTarget->IsDying())
				{
					targets.RemoveNonCyclicAtIndex(i);
				}
				else
				{
					//AnimationManager::AddAnimation(healAnimation, currentTarget->GetPosition(), healAnimationSize);
				}
			}
			AbilityStack::AddAbility(this, aCard, targets);
		}
	}
}