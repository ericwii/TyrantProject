#include "stdafx.h"
#include "WeakenAbility.h"

Vector2<float> weakenAnimationSize(1.5f, 2.f);
AnimationData weakenAnimation = AnimationData
(
	"Data/Textures/Animations/weakenAnimation.png",
	8,
	2,
	20.f,
	false
);

WeakenAbility::WeakenAbility(const string & aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData): AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/weakenIcon.png";
	myAbilityType = eAbilityTypes::eWeaken;
	myCardText.Insert("Weaken", 0);
}

WeakenAbility::~WeakenAbility()
{
}

void WeakenAbility::OnPreCombat(Card * aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::IsOffCooldownNextTurn | eFindTargetCondition::HasAttack);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, &weakenAnimation, weakenAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::IsOffCooldownNextTurn | eFindTargetCondition::HasAttack);
			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, &weakenAnimation, weakenAnimationSize);
			}
		}
	}
}

void WeakenAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::IsOffCooldownNextTurn | eFindTargetCondition::HasAttack);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, &weakenAnimation, weakenAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::IsOffCooldownNextTurn | eFindTargetCondition::HasAttack);
			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, &weakenAnimation, weakenAnimationSize);
			}
		}
	}
}

void WeakenAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Weaken(myNumber + aCaster->GetStatusEffectNumber(eStatusEffectType::Augment));
	}
}
