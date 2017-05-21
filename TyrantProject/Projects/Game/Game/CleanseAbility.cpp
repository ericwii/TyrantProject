#include "stdafx.h"
#include "CleanseAbility.h"


Vector2<float> cleanseAnimationSize(2.f, 2.f);
AnimationData cleanseAnimation = AnimationData
(
	"Data/Textures/Animations/strikeAnimation.png",
	18,
	4,
	30.f,
	false
	);

CleanseAbility::CleanseAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/cleanseIcon.png";
	myAbilityType = eAbilityTypes::eCleanse;
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
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, nullptr, cleanseAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, nullptr, cleanseAnimationSize);
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
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, nullptr, cleanseAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, nullptr, cleanseAnimationSize);
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
		Card* target = FindTarget(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown);
		if (target != nullptr)
		{
			AbilityStack::AddAbility(this, aUser, target, nullptr, cleanseAnimationSize);
		}
	}
	else if (mySuffix == "all onattacked")
	{
		CU::GrowingArray<Card*> targets = FindAllTargets(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown);
		if (targets.Size() > 0)
		{
			AbilityStack::AddAbility(this, aUser, targets, nullptr, cleanseAnimationSize);
		}
	}
}
