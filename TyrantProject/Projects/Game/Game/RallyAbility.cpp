#include "stdafx.h"
#include "RallyAbility.h"

Vector2<float> rallyAnimationSize(1.5f, 2.f);
AnimationData rallyAnimation = AnimationData
(
	"Data/Textures/Animations/rallyAnimation.png",
	8,
	2,
	20.f,
	false
);

RallyAbility::RallyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : AbilityBase(aSuffix, aNumber, aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/rallyIcon.png";
	myAbilityType = eAbilityTypes::eRally;
	myCardText.Insert("Rally", 0);
}


RallyAbility::~RallyAbility()
{
}


void RallyAbility::OnPreCombat(Card* aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, &rallyAnimation, rallyAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeTargetedByFriendly);
			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, &rallyAnimation, rallyAnimationSize);
			}
		}
	}
}

void RallyAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Rally(myNumber + aCaster->GetStatusEffectNumber(eStatusEffectType::Augment));
		AnimationManager::AddAnimation(rallyAnimation, someTargets[i]->GetPosition(), rallyAnimationSize);
	}
}

void RallyAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, &rallyAnimation, rallyAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, &rallyAnimation, rallyAnimationSize);
			}
		}
	}
}
