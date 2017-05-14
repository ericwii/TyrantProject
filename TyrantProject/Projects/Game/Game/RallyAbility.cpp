#include "stdafx.h"
#include "RallyAbility.h"

Vector2<float> rallyAnimationSize(2.f, 2.f);
AnimationData rallyAnimation = AnimationData
(
	"Data/Textures/Animations/strikeAnimation.png",
	18,
	4,
	30.f,
	false
);

RallyAbility::RallyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/rallyIcon.png";
}


RallyAbility::~RallyAbility()
{
}


void RallyAbility::OnPreCombat(Card* aCard)
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
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards());

			if (targets.Size() > 0)
			{
				for (int i = targets.Size() - 1; i >= 0; --i)
				{
					if (targets[i]->GetCooldown() > 0)
					{
						targets.RemoveCyclicAtIndex(i);
					}
				    //AnimationManager::AddAnimation(rallyAnimation, targets[i]->GetPosition(), rallyAnimationSize);
				}
				AbilityStack::AddAbility(this, aCard, targets);
			}
		}
	}
}

void RallyAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Rally(myNumber);
	}
}