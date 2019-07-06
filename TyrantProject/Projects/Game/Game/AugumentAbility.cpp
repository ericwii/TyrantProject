#include "stdafx.h"
#include "AugumentAbility.h"


Vector2<float> agumentAnimationSize(1.5f, 2.f);
AnimationData agumentAnimation = AnimationData
(
	"Data/Textures/Animations/AugmentAnimation.png",
	8,
	2,
	20.f,
	false
	);

AugmentAbility::AugmentAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : AbilityBase(aSuffix, aNumber, aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/augmentIcon.png";
	myAbilityType = eAbilityTypes::eAgument;
	myCardText.Insert("Augment", 0);
}


AugmentAbility::~AugmentAbility()
{
}

void AugmentAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->AddStatusEffect(eStatusEffectType::Augment, iconTexturePath, myNumber);
	}
}

void AugmentAbility::OnCalculateAttack(AttackData & data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, &agumentAnimation, agumentAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, &agumentAnimation, agumentAnimationSize);
			}
		}
	}
}

void AugmentAbility::OnPreCombat(Card * aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, &agumentAnimation, agumentAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, &agumentAnimation, agumentAnimationSize);
			}
		}
	}
}

void AugmentAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	anAttacker;
	someDamage;

	if (mySuffix == "onattacked")
	{
		Card* target = FindTarget(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeTargetedByFriendly);
		if (target != nullptr)
		{
			AbilityStack::AddAbility(this, aUser, target, &agumentAnimation, agumentAnimationSize);
		}
	}
	else if (mySuffix == "all onattacked")
	{
		CU::GrowingArray<Card*> targets = FindAllTargets(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::CanBeTargetedByFriendly);
		if (targets.Size() > 0)
		{
			AbilityStack::AddAbility(this, aUser, targets, &agumentAnimation, agumentAnimationSize);
		}
	}
}
