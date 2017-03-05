#include "stdafx.h"
#include "StrikeAbility.h"

Vector2<float> strikeAnimationSize(2.f, 2.f);
AnimationData strikeAnimation = AnimationData
(
		"Data/Textures/strikeAnimation.png",
		18,
		4,
		30.f,
		false
);

float strikeDelay = 0.2f;



StrikeAbility::StrikeAbility(const string& aSuffix, char aNumber) : AbilityBase(aSuffix, aNumber)
{
	iconTexturePath = "Data/Textures/Icons/strikeIcon.png";
}

StrikeAbility::~StrikeAbility()
{
}


void StrikeAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
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

void StrikeAbility::OnPreCombat(Card* aCard)
{
	if (aCard->GetCooldown() < 1)
	{
		Player* opponent = aCard->GetOwner()->GetOpponent();
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(opponent->GetAssaultCards());

			if (target != nullptr)
			{
				target = target->OnTargeted();
				if (target != nullptr)
				{
					AnimationManager::AddAnimation(strikeAnimation, target->GetPosition(), strikeAnimationSize);
					AbilityStack::AddAbility(this, aCard, target, strikeDelay);
				}
			}
		}
		else if (mySuffix == "all")
		{
			Card* currentTarget;
			CU::GrowingArray<Card*> targets = opponent->GetAssaultCards();
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
					AnimationManager::AddAnimation(strikeAnimation, currentTarget->GetPosition(), strikeAnimationSize);
				}
			}
			AbilityStack::AddAbility(this, aCard, targets, strikeDelay);
		}
	}
}

void StrikeAbility::OnAttacked(char& someDamage)
{
	someDamage;
	if (mySuffix == "on attacked")
	{

	}
}



//Private Methods

Card* StrikeAbility::FindTarget(CU::GrowingArray<Card*>& cards)
{
	if (cards.Size() > 0)
	{
		int randomIndex = rand() % cards.Size();
		for (int searchCount = 0; searchCount < cards.Size(); ++searchCount)
		{
			if (!cards[randomIndex]->IsDying())
			{
				return cards[randomIndex];
			}

			++randomIndex;
			randomIndex %= cards.Size();
		}
	}
	return nullptr;
}