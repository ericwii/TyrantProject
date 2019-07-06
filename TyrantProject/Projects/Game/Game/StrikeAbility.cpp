#include "stdafx.h"
#include "StrikeAbility.h"

Vector2<float> strikeAnimationSize(2.f, 2.f);
AnimationData strikeAnimation = AnimationData
(
		"Data/Textures/Animations/strikeAnimation.png",
		18,
		4,
		30.f,
		false
);

float strikeDelay = 0.2f;



StrikeAbility::StrikeAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : AbilityBase(aSuffix, aNumber, aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/strikeIcon.png";
	myAbilityType = eAbilityTypes::eStrike;
	myCardText.Insert("Strike", 0);
}

StrikeAbility::~StrikeAbility()
{
}


void StrikeAbility::DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	char originalDamage = myNumber + aCaster->GetStatusEffectNumber(eStatusEffectType::Augment);
	char damage = originalDamage;
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		if (!someTargets[i]->IsDying())
		{
			someTargets[i]->TakeDamage(damage);
			damage = originalDamage;
		}
	}
}

void StrikeAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		Player* opponent = data.attacker->GetOwner()->GetOpponent();
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(opponent->GetAssaultCards());

			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, &strikeAnimation,strikeAnimationSize, strikeDelay);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(opponent->GetAssaultCards());

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, &strikeAnimation, strikeAnimationSize, strikeDelay);
			}
		}
	}
}

void StrikeAbility::OnPreCombat(Card* aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetOpponent()->GetAssaultCards());
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, &strikeAnimation, strikeAnimationSize, strikeDelay);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetOpponent()->GetAssaultCards());

			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, &strikeAnimation, strikeAnimationSize, strikeDelay);
			}
		}
	}
}

void StrikeAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	anAttacker;
	someDamage;

	Player* opponent = aUser->GetOwner()->GetOpponent();
	if (mySuffix == "onattacked")
	{	
		Card* target = FindTarget(opponent->GetAssaultCards());

		if (target != nullptr)
		{
			AbilityStack::AddAbility(this, aUser, target, &strikeAnimation, strikeAnimationSize, strikeDelay);
		}
		
	}
	else if(mySuffix == "all onattacked")
	{
		CU::GrowingArray<Card*> targets = FindAllTargets(opponent->GetAssaultCards());

		if (targets.Size() > 0)
		{
			AbilityStack::AddAbility(this, aUser, targets, &strikeAnimation, strikeAnimationSize, strikeDelay);
		}
	}
}

void StrikeAbility::OnPlay(Card* aCard)
{
	Player* opponent = aCard->GetOwner()->GetOpponent();

	if (mySuffix == "onplay")
	{
		Card* target = FindTarget(opponent->GetAssaultCards());

		if (target != nullptr)
		{
			AbilityStack::AddAbility(this, aCard, target, &strikeAnimation, strikeAnimationSize, strikeDelay);
		}

	}
	else if (mySuffix == "all onplay")
	{
		CU::GrowingArray<Card*> targets = FindAllTargets(opponent->GetAssaultCards());

		if (targets.Size() > 0)
		{
			AbilityStack::AddAbility(this, aCard, targets, &strikeAnimation, strikeAnimationSize, strikeDelay);
		}
	}
}
