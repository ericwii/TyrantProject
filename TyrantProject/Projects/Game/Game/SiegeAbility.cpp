#include "stdafx.h"
#include "SiegeAbility.h"


Vector2<float> siegeAnimationSize(2.f, 2.f);
AnimationData siegeAnimation = AnimationData
(
	"Data/Textures/Animations/strikeAnimation.png",
	18,
	4,
	30.f,
	false
);

float siegeDelay = 0.2f;

SiegeAbility::SiegeAbility(const string & aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/siegeIcon.png";
}

SiegeAbility::~SiegeAbility()
{
}

void SiegeAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		if (!someTargets[i]->IsDying())
		{
			someTargets[i]->TakeDamage(myNumber);
		}
	}
}

void SiegeAbility::OnPreCombat(Card * aCard)
{
	if (aCard->GetCooldown() < 1)
	{
		Player* opponent = aCard->GetOwner()->GetOpponent();
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(opponent->GetStructureCards());

			if (target != nullptr)
			{
				target = target->OnTargeted();
				if (target != nullptr)
				{
					AnimationManager::AddAnimation(siegeAnimation, target->GetPosition(), siegeAnimationSize);
					AbilityStack::AddAbility(this, aCard, target, siegeDelay);
				}
			}
		}
		else if (mySuffix == "all")
		{
			Card* currentTarget;
			CU::GrowingArray<Card*> targets = opponent->GetStructureCards();
			for (int i = targets.Size() - 1; i >= 0; --i)
			{
				currentTarget = targets[i];
				if (!currentTarget->IsDying())
				{
					currentTarget = currentTarget->OnTargeted();
				}

				if (currentTarget == nullptr || currentTarget->IsDying())
				{
					targets.RemoveNonCyclicAtIndex(i);
				}
				else
				{
					AnimationManager::AddAnimation(siegeAnimation, currentTarget->GetPosition(), siegeAnimationSize);
				}
			}
			AbilityStack::AddAbility(this, aCard, targets, siegeDelay);
		}
	}
}

void SiegeAbility::OnAttacked(char & someDamage)
{
	someDamage;
}
