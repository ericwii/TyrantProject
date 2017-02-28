#include "stdafx.h"
#include "StrikeAbility.h"

Vector2<float> strikeAnimationSize(2.f, 2.f);
AnimationData strikeAnimation = AnimationData
(
		"Data/Textures/strikeAnimation.png",
		18,
		4,
		16.f,
		false
);



StrikeAbility::StrikeAbility(const string& aSuffix, char aNumber) : AbilityBase(aSuffix, aNumber)
{
	myIconTexturePath = "Data/Textures/Icons/strikeIcon.png";
}

StrikeAbility::~StrikeAbility()
{
}



void StrikeAbility::OnPreCombat(Card* aCard)
{
	if (mySuffix.Lenght() == 0 && aCard->GetCooldown() < 1)
	{
		//Player* opponent = aCard->GetOwner()->GetOpponent();
	}
}

void StrikeAbility::OnAttacked(OnComingAction& anAction)
{
	anAction;
	if (mySuffix == "on attacked")
	{

	}
}


//Private Methods

Card* StrikeAbility::FindTarget(CU::GrowingArray<Card*>& cards)
{
	if (cards.Size() > 0)
	{
		int randomIndex = rand() % cards.Size();
		for (int searchCount = 0; searchCount < cards.Size(); ++searchCount)
		{
			if (!cards[randomIndex]->IsDying())
			{
				return cards[randomIndex];
			}

			++randomIndex;
			randomIndex %= cards.Size();
		}
	}
	return nullptr;
}