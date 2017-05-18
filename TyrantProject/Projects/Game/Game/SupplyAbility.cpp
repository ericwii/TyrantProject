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

SupplyAbility::SupplyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/supplyIcon.png";
	myAbilityType = eAbilityTypes::eSupply;
	myTargets.Allocate(2);
	
}


SupplyAbility::~SupplyAbility()
{
	
}

void SupplyAbility::OnBeforeAttack(Card * aCard, Card * currentTarget, char & someDamage)
{
	currentTarget;
	someDamage;

	if (aCard->GetCooldown() < 1 && mySuffix.Lenght() == 0)
	{
		FindAdjecentTargets(aCard, myTargets);
		AbilityStack::AddAbility(this, aCard, myTargets);
	}
}

void SupplyAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	someDamage;
	anAttacker;

	if (mySuffix == "onattacked")
	{
		FindAdjecentTargets(aUser, myTargets);
		AbilityStack::AddAbility(this, aUser, myTargets);
	}
}

void SupplyAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster->Heal(myNumber);
	AnimationManager::AddAnimation(supplyAnimation, aCaster->GetPosition(), supplyAnimationSize);
	
	for (int i = 0; i < someTargets.Size(); i++)
	{
		someTargets[i]->Heal(myNumber);
		AnimationManager::AddAnimation(supplyAnimation, someTargets[i]->GetPosition(), supplyAnimationSize);
	}

	myTargets.RemoveAll();

}
