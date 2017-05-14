#include "stdafx.h"
#include "RefreshAbility.h"

Vector2<float> refreshAnimationSize(0.5f, 0.5f);
AnimationData refreshAnimation = AnimationData
(
	"Data/Textures/Animations/refreshAnimation.png",
	5,
	1,
	20.f,
	false
);


RefreshAbility::RefreshAbility() : AbilityBase()
{
	iconTexturePath = "Data/Textures/Icons/Skills/refreshIcon.png";
}


RefreshAbility::~RefreshAbility()
{
}

void RefreshAbility::OnCleanUp(Card * aCard)
{
	if (aCard->IsAtMaxHealth() == false)
	{
		AbilityStack::AddAbility(this, aCard, aCard, 0.2f);
	}
}

void RefreshAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	someTargets;

	int heal = 100;
	aCaster->Heal((char)heal);
	AnimationManager::AddAnimation(refreshAnimation, aCaster->GetPosition(), refreshAnimationSize);
}
