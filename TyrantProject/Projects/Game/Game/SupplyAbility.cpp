#include "stdafx.h"
#include "SupplyAbility.h"


Vector2<float> supplyAnimationSize(0.3f, 0.5f);
AnimationData supplyAnimation = AnimationData
(
	"Data/Textures/Animations/refreshGreenAnimation.png",
	5,
	1,
	20.f,
	false
);

SupplyAbility::SupplyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/supplyIcon.png";
	myAbilityType = eAbilityTypes::eSupply;
	myTargets.Allocate(2);
	myCardText.Insert("Supply", 0);
}


SupplyAbility::~SupplyAbility()
{
	
}

void SupplyAbility::OnCalculateAttack(AttackData& data)
{
	if (data.attacker->GetCooldown() < 1 && mySuffix.Lenght() == 0)
	{
		FindAdjecentTargets(data.attacker);
		AbilityStack::AddAbility(this, data.attacker, myTargets, &supplyAnimation, supplyAnimationSize);
	}
}

void SupplyAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	someDamage;
	anAttacker;

	if (mySuffix == "onattacked")
	{
		FindAdjecentTargets(aUser);
		AbilityStack::AddAbility(this, aUser, myTargets, &supplyAnimation, supplyAnimationSize);
	}
}

void SupplyAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	char augment = aCaster->GetStatusEffectNumber(eStatusEffectType::Augment);

	aCaster->Heal(myNumber + augment);
	
	for (int i = 0; i < someTargets.Size(); i++)
	{
		someTargets[i]->Heal(myNumber + augment);
	}

	myTargets.RemoveAll();

}
