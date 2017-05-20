#include "stdafx.h"
#include "SwipeAbility.h"

Vector2<float> swipeAnimationSize(2.f, 2.f);
AnimationData swipeAnimation = AnimationData
(
	"Data/Textures/Animations/swipeAnimation.png",
	10,
	2,
	20.f,
	false
);


SwipeAbility::SwipeAbility()
{
	myAbilityType = eAbilityTypes::eSwipe;
	iconTexturePath = "Data/Textures/Icons/Skills/swipeIcon.png";
	myTargets.Allocate(2);
}


SwipeAbility::~SwipeAbility()
{
}

void SwipeAbility::OnCalculateAttack(AttackData & data)
{
	FindAdjecentTargets(data.mainTarget, myTargets, 1);
	if (myTargets.Size() == 1)
	{
		data.extraTargets[0] = myTargets[0];
		data.attackAnimation = &swipeAnimation;
	}
	else if (myTargets.Size() == 2)
	{
		data.extraTargets[0] = myTargets[0];
		data.extraTargets[1] = myTargets[1];
		data.attackAnimation = &swipeAnimation;
	}
}
