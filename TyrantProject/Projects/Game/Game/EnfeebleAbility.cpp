#include "stdafx.h"
#include "EnfeebleAbility.h"


Vector2<float> enfeebleAnimationSize(2.f, 2.f);
AnimationData enfeebleAnimation = AnimationData
(
	"Data/Textures/Animations/strikeAnimation.png",
	18,
	4,
	30.f,
	false
	);

EnfeebleAbility::EnfeebleAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData): AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/enfeebleIcon.png";
	myAbilityType = eAbilityTypes::eEnfeeble;

	myCardText.Insert("Enfeeble", 0);
}


EnfeebleAbility::~EnfeebleAbility()
{
}

void EnfeebleAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->AddStatusEffect(eStatusEffectType::Enfeeble, iconTexturePath, myNumber + aCaster->GetStatusEffectNumber(eStatusEffectType::Augment));
	}
}

void EnfeebleAbility::OnCalculateAttack(AttackData & data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::None);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, nullptr, enfeebleAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::None);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, nullptr, enfeebleAnimationSize);
			}
		}
	}
}

void EnfeebleAbility::OnPreCombat(Card * aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::None);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, nullptr, enfeebleAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::None);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, nullptr, enfeebleAnimationSize);
			}
		}
	}
}
