#include "stdafx.h"
#include "WallAbility.h"


WallAbility::WallAbility()
{
	iconTexturePath = "Data/Textures/Icons/Skills/wallIcon.png";
	myAbilityType = eAbilityTypes::eWall;
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
