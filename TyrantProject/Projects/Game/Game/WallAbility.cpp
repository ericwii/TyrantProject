#include "stdafx.h"
#include "WallAbility.h"


WallAbility::WallAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/wallIcon.png";
	myAbilityType = eAbilityTypes::eWall;
	myCardText = "Wall";
}


WallAbility::~WallAbility()
{
}

void WallAbility::OnCommanderAttack(Card*& aCurrentTarget, Card* aUser)
{
	if (aUser->IsDying() == false)
	{
		aCurrentTarget = aUser;
	}
}
