#include "stdafx.h"
#include "AgumentAbility.h"


Vector2<float> agumentAnimationSize(2.f, 2.f);
AnimationData agumentAnimation = AnimationData
(
	"Data/Textures/Animations/strikeAnimation.png",
	18,
	4,
	30.f,
	false
	);

AgumentAbility::AgumentAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/augmentIcon.png";
	myAbilityType = eAbilityTypes::eAgument;
}


AgumentAbility::~AgumentAbility()
{
}

void AgumentAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Agument(myNumber);
	}
}

void AgumentAbility::OnCalculateAttack(AttackData & data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, nullptr, agumentAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, nullptr, agumentAnimationSize);
			}
		}
	}
}

void AgumentAbility::OnPreCombat(Card * aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, nullptr, agumentAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, nullptr, agumentAnimationSize);
			}
		}
	}
}

void AgumentAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	anAttacker;
	someDamage;

	if (mySuffix == "onattacked")
	{
		Card* target = FindTarget(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);
		if (target != nullptr)
		{
			AbilityStack::AddAbility(this, aUser, target, nullptr, agumentAnimationSize);
		}
	}
	else if (mySuffix == "all onattacked")
	{
		CU::GrowingArray<Card*> targets = FindAllTargets(aUser->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);
		if (targets.Size() > 0)
		{
			AbilityStack::AddAbility(this, aUser, targets, nullptr, agumentAnimationSize);
		}
	}
}
