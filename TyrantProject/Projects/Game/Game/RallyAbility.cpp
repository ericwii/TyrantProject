#include "stdafx.h"
#include "RallyAbility.h"

Vector2<float> rallyAnimationSize(1.5f, 2.f);
AnimationData rallyAnimation = AnimationData
(
	"Data/Textures/Animations/rallyAnimation.png",
	8,
	2,
	20.f,
	false
);

RallyAbility::RallyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/rallyIcon.png";
	myAbilityType = eAbilityTypes::eRally;
}


RallyAbility::~RallyAbility()
{
}


void RallyAbility::OnPreCombat(Card* aCard)
{
	aCard;
}

void RallyAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		someTargets[i]->Rally(myNumber);
		AnimationManager::AddAnimation(rallyAnimation, someTargets[i]->GetPosition(), rallyAnimationSize);
	}
}

void RallyAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetAssaultCards(), eFindTargetCondition::IsOffCooldown);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets);
			}
		}
	}
}
