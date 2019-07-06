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


HealAbility::HealAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : AbilityBase(aSuffix, aNumber, aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/healIcon.png";
	myAbilityType = eAbilityTypes::eHeal;

	myCardText.Insert("Heal", 0);
}

HealAbility::~HealAbility()
{
}



void HealAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Heal(myNumber + aCaster->GetStatusEffectNumber(eStatusEffectType::Augment));
	}
}

void HealAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsDamaged | eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, nullptr, healAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsDamaged | eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, nullptr, healAnimationSize);
			}
		}
	}
}

void HealAbility::OnPreCombat(Card* aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsDamaged | eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, nullptr, healAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsDamaged | eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, nullptr, healAnimationSize);
			}
		}
	}
}

void HealAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	anAttacker;
	someDamage;

	if (mySuffix == "onattacked")
	{
		Card* target = FindTarget(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsDamaged | eFindTargetCondition::CanBeTargetedByFriendly);
		if (target != nullptr)
		{
			AbilityStack::AddAbility(this, aUser, target, nullptr, healAnimationSize);
		}
	}
	else if(mySuffix == "all onattacked")
	{
		CU::GrowingArray<Card*> targets = FindAllTargets(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsDamaged | eFindTargetCondition::CanBeTargetedByFriendly);
		if (targets.Size() > 0)
		{
			AbilityStack::AddAbility(this, aUser, targets, nullptr, healAnimationSize);
		}
	}
}
