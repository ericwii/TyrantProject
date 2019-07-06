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


SwipeAbility::SwipeAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	myAbilityType = eAbilityTypes::eSwipe;
	iconTexturePath = "Data/Textures/Icons/Skills/swipeIcon.png";
	myTargets.Allocate(2);
	myCardText = "Swipe";
}


SwipeAbility::~SwipeAbility()
{
}

void SwipeAbility::OnCalculateAttack(AttackData & data)
{
	CU::GrowingArray<Card*>& cardsToSearch = data.mainTarget->GetOwner()->GetAssaultCards();

	for (int i = 0; i < cardsToSearch.Size(); ++i)
	{
		if (cardsToSearch[i] == data.mainTarget)
		{
			if (i > 0 && cardsToSearch[i - 1]->IsDying() == false)
			{
				data.extraTargets[0] = cardsToSearch[i - 1];
				data.attackAnimation = &swipeAnimation;
			}

			if (i + 1 < cardsToSearch.Size() && cardsToSearch[i + 1]->IsDying() == false)
			{
				data.extraTargets[1] = cardsToSearch[i + 1];
				data.attackAnimation = &swipeAnimation;
			}

			break;
		}
	}
}
