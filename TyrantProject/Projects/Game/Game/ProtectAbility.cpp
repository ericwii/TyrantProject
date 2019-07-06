#include "stdafx.h"
#include "ProtectAbility.h"


Vector2<float> protectAnimationSize(1.5f, 2.f);
AnimationData protectAnimation = AnimationData
(
	"Data/Textures/Animations/protectAnimation.png",
	20,
	4,
	30.f,
	false
);

ProtectAbility::ProtectAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : AbilityBase(aSuffix, aNumber, aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/protectIcon.png";
	myAbilityType = eAbilityTypes::eProtect;
	myCardText.Insert("Protect", 0);
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
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				//AbilityStack::AddAbility(this, data.attacker, target, &protectAnimation, protectAnimationSize);
				StoredAbility abilityInfo;
				abilityInfo.ability = this;
				abilityInfo.caster = data.attacker;
				abilityInfo.animationData = &protectAnimation;
				abilityInfo.animationSize = protectAnimationSize;
				abilityInfo.targets.Allocate(1);
				abilityInfo.targets[0] = target;
				abilityInfo.animationFlipY = true;
				AbilityStack::AddAbility(abilityInfo);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				//AbilityStack::AddAbility(this, data.attacker, targets, &protectAnimation, protectAnimationSize);
				StoredAbility abilityInfo;
				abilityInfo.ability = this;
				abilityInfo.caster = data.attacker;
				abilityInfo.animationData = &protectAnimation;
				abilityInfo.animationSize = protectAnimationSize;
				abilityInfo.targets = targets;
				abilityInfo.animationFlipY = true;
				AbilityStack::AddAbility(abilityInfo);
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
			Card* target = FindTarget(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::CanBeTargetedByFriendly);
			if (target != nullptr)
			{
				//AbilityStack::AddAbility(this, aCard, target, &protectAnimation, protectAnimationSize);
				StoredAbility abilityInfo;
				abilityInfo.ability = this;
				abilityInfo.caster = aCard;
				abilityInfo.animationData = &protectAnimation;
				abilityInfo.animationSize = protectAnimationSize;
				abilityInfo.targets.Allocate(1);
				abilityInfo.targets[0] = target;
				abilityInfo.animationFlipY = true;
				AbilityStack::AddAbility(abilityInfo);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetAssaultCards(), eFindTargetCondition::CanBeTargetedByFriendly);

			if (targets.Size() > 0)
			{
				//AbilityStack::AddAbility(this, aCard, targets, &protectAnimation, protectAnimationSize);
				StoredAbility abilityInfo;
				abilityInfo.ability = this;
				abilityInfo.caster = aCard;
				abilityInfo.animationData = &protectAnimation;
				abilityInfo.animationSize = protectAnimationSize;
				abilityInfo.targets = targets;
				abilityInfo.animationFlipY = true;
				AbilityStack::AddAbility(abilityInfo);
			}
		}
	}
}
