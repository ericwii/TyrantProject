#include "stdafx.h"
#include "SiegeAbility.h"


Vector2<float> siegeAnimationSize(1.9f, 2.3f);
AnimationData siegeAnimation = AnimationData
(
	"Data/Textures/Animations/siegeAnimation.png",
	12,
	3,
	20.f,
	false
);

SiegeAbility::SiegeAbility(const string & aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/siegeIcon.png";
	myAbilityType = eAbilityTypes::eSiege;
	myCardText.Insert("Siege", 0);
}

SiegeAbility::~SiegeAbility()
{
}

void SiegeAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster;
	char damage = myNumber + aCaster->GetStatusEffectNumber(eStatusEffectType::Augment);
	for (int i = 0; i < someTargets.Size(); ++i)
	{
		if (!someTargets[i]->IsDying())
		{
			someTargets[i]->TakeDamage(damage);
		}
	}
}

void SiegeAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1)
	{
		Player* opponent = data.attacker->GetOwner()->GetOpponent();
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(opponent->GetStructureCards());

			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, data.attacker, target, &siegeAnimation, siegeAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(opponent->GetStructureCards());
			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, data.attacker, targets, &siegeAnimation, siegeAnimationSize);
			}
		}
	}
}

void SiegeAbility::OnPreCombat(Card * aCard)
{
	if ((aCard->GetCardType() == eCardType::Commander || aCard->GetCardType() == eCardType::Structure) && aCard->GetCooldown() < 1)
	{
		if (mySuffix.Lenght() == 0)
		{
			Card* target = FindTarget(aCard->GetOwner()->GetOpponent()->GetStructureCards());
			if (target != nullptr)
			{
				AbilityStack::AddAbility(this, aCard, target, &siegeAnimation, siegeAnimationSize);
			}
		}
		else if (mySuffix == "all")
		{
			CU::GrowingArray<Card*> targets = FindAllTargets(aCard->GetOwner()->GetOpponent()->GetStructureCards());
			if (targets.Size() > 0)
			{
				AbilityStack::AddAbility(this, aCard, targets, &siegeAnimation, siegeAnimationSize);
			}
		}
	}
}
