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

void SupplyAbility::OnPreCombat(Card * aCard)
{
	if (aCard->GetCooldown() < 1)
	{
		for (int i = 0; i < aCard->GetOwner()->GetAssaultCards().Size(); i++)
		{
			if (aCard->GetOwner()->GetAssaultCards()[i] == aCard)
			{

				if (i - 1 >= 0)
				{
					if (aCard->GetOwner()->GetAssaultCards()[i - 1]->IsDying() == false)
					{
						myTargets.Add(aCard->GetOwner()->GetAssaultCards()[i - 1]);
					}
				}

				if (i + 1 <= aCard->GetOwner()->GetAssaultCards().Size() - 1)
				{
					if (aCard->GetOwner()->GetAssaultCards()[i + 1]->IsDying() == false)
					{
						myTargets.Add(aCard->GetOwner()->GetAssaultCards()[i + 1]);
					}
				}
			}
		}
		AbilityStack::AddAbility(this, aCard, myTargets);
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
