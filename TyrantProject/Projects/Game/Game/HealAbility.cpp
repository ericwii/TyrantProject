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


HealAbility::HealAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/healIcon.png";
	myAbilityType = eAbilityTypes::eHeal;
}

HealAbility::~HealAbility()
{
}



void HealAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Heal(myNumber);
	}
}

void HealAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsDamaged);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsDamaged);

			if (targets.Size() > 0)
			{
				//for (int i = 0; i < targets.Size(); ++i)
				//{
				//AnimationManager::AddAnimation(healAnimation, targets[i]->GetPosition(), healAnimationSize);
				//}
				AbilityStack::AddAbility(this, data.attacker, targets);
			}
		}
	}
}

void HealAbility::OnPreCombat(Card* aCard)
{
	aCard;
}