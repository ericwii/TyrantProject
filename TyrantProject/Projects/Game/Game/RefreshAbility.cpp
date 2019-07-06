#include "stdafx.h"
#include "RefreshAbility.h"

Vector2<float> refreshAnimationSize(0.3f, 0.5f);
AnimationData refreshAnimation = AnimationData
(
	"Data/Textures/Animations/refreshAnimation.png",
	5,
	1,
	20.f,
	false
);


RefreshAbility::RefreshAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/refreshIcon.png";
	myAbilityType = eAbilityTypes::eRefresh;
	myCardText = "Refresh";
}

RefreshAbility::~RefreshAbility()
{
}


void RefreshAbility::OnCleanUp(Card * aCard)
{
	if (aCard->IsAtMaxHealth() == false)
	{
		int heal = 100;
		aCard->Heal((char)heal);
		AnimationManager::AddAnimation(refreshAnimation, aCard->GetPosition(), refreshAnimationSize);
	}
}
