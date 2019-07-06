#include "stdafx.h"
#include "CleanseAbility.h"


Vector2<float> cleanseAnimationSize(1.5f, 2.f);
AnimationData cleanseAnimation = AnimationData
(
	"Data/Textures/Animations/cleanseAnimation.png",
	8,
	2,
	20.f,
	false
	);

CleanseAbility::CleanseAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData): AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/cleanseIcon.png";
	myAbilityType = eAbilityTypes::eCleanse;

	myCardText.Insert("Cleanse", 0);
}


CleanseAbility::~CleanseAbility()
{
}

void CleanseAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Cleanse();
	}
}

void CleanseAbility::OnCalculateAttack(AttackData & data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeCleansed | eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, &cleanseAnimation, cleanseAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeCleansed | eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, &cleanseAnimation, cleanseAnimationSize);
			}
		}
	}
}

void CleanseAbility::OnPreCombat(Card * aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeCleansed | eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, &cleanseAnimation, cleanseAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeCleansed | eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, &cleanseAnimation, cleanseAnimationSize);
			}
		}
	}
}

void CleanseAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	anAttacker;
	someDamage;

	if (mySuffix == "onattacked")
	{
		Card* target = FindTarget(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeCleansed | eFindTargetCondition::CanBeTargetedByFriendly);
		if (target != nullptr)
		{
			AbilityStack::AddAbility(this, aUser, target, &cleanseAnimation, cleanseAnimationSize);
		}
	}
	else if (mySuffix == "all onattacked")
	{
		CU::GrowingArray<Card*> targets = FindAllTargets(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown | eFindTargetCondition::CanBeCleansed | eFindTargetCondition::CanBeTargetedByFriendly);
		if (targets.Size() > 0)
		{
			AbilityStack::AddAbility(this, aUser, targets, &cleanseAnimation, cleanseAnimationSize);
		}
	}
}
