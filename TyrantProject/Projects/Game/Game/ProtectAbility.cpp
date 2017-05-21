#include "stdafx.h"
#include "ProtectAbility.h"


Vector2<float> protectAnimationSize(2.f, 2.f);
AnimationData protectAnimation = AnimationData
(
	"Data/Textures/Animations/strikeAnimation.png",
	18,
	4,
	30.f,
	false
	);

ProtectAbility::ProtectAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/protectIcon.png";
	myAbilityType = eAbilityTypes::eProtect;
}


ProtectAbility::~ProtectAbility()
{
}

void ProtectAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->AddStatusEffect(eStatusEffectType::Protect, iconTexturePath, myNumber + aCaster->GetStatusEffectNumber(eStatusEffectType::Augment));
	}
}

void ProtectAbility::OnCalculateAttack(AttackData & data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, nullptr, protectAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, nullptr, protectAnimationSize);
			}
		}
	}
}

void ProtectAbility::OnPreCombat(Card * aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, nullptr, protectAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::None);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, nullptr, protectAnimationSize);
			}
		}
	}
}
