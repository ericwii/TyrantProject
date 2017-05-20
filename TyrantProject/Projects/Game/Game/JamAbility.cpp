#include "stdafx.h"
#include "JamAbility.h"

Vector2<float> jamAnimationSize(2.f, 2.f);
AnimationData jamAnimation = AnimationData
(
	"Data/Textures/Animations/strikeAnimation.png",
	18,
	4,
	30.f,
	false
	);

JamAbility::JamAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	myAbilityType = eAbilityTypes::eJam;
	iconTexturePath = "Data/Textures/Icons/Skills/jamIcon.png";
}


JamAbility::~JamAbility()
{
}

void JamAbility::OnCalculateAttack(AttackData & data)
{
	if (data.attacker->GetCooldown() < 1)
	{
	
			if (mySuffix.Lenght() == 0)
			{
				Card* target = FindTarget(data.attacker->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::IsOffCooldownNextTurn);
				if (target != nullptr)
				{
					AbilityStack::AddAbility(this, data.attacker, target, nullptr, jamAnimationSize);
				}
			}
			else if (mySuffix == "all")
			{
				CU::GrowingArray<Card*> targets = FindAllTargets(data.attacker->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::IsOffCooldownNextTurn);

				if (targets.Size() > 0)
				{
					AbilityStack::AddAbility(this, data.attacker, targets, nullptr, jamAnimationSize);
				}
			}
		
	}
}

void JamAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;

	for (int i = 0; i < someTargets.Size(); ++i)
	{
		if ((rand() % 2) == 1)
		{
			someTargets[i]->Jam();
		}
	}
}

void JamAbility::OnPreCombat(Card * aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::IsOffCooldownNextTurn);
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, nullptr, jamAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetOpponent()->GetAssaultCards(), eFindTargetCondition::IsOffCooldownNextTurn);

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, nullptr, jamAnimationSize);
			}
		}
	}
}