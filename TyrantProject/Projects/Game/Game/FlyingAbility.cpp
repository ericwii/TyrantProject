#include "stdafx.h"
#include "FlyingAbility.h"


Vector2<float> flyingAnimationSize(1.5f, 2.f);
AnimationData flyingAnimation = AnimationData
(
	"Data/Textures/Animations/flyingAnimation.png",
	8,
	2,
	15.f,
	false
	);

FlyingAbility::FlyingAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/flyingIcon.png";
	myAbilityType = eAbilityTypes::eFlying;
	myCardText = "Flying";
}


FlyingAbility::~FlyingAbility()
{
}

void FlyingAbility::OnAttacked(Card* aUser, char & someDamage, Card * anAttacker)
{
	for (int i = 0; i < anAttacker->GetAbilities().Size(); i++)
	{
		if (anAttacker->GetAbilities()[i]->GetAbilityType() == eAbilityTypes::eAntiAir)
		{
			someDamage += anAttacker->GetAbilities()[i]->GetNumber();
			return;
		}
		else if(anAttacker->GetAbilities()[i]->GetAbilityType() == eAbilityTypes::eFlying)
		{
			return;
		}
	}

	if ((rand() % 2) == 1)
	{
		
		AnimationManager::AddAnimation(flyingAnimation, aUser->GetPosition(), flyingAnimationSize);
		someDamage = 0;
	}
}
