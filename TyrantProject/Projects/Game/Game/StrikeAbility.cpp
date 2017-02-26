#include "stdafx.h"
#include "StrikeAbility.h"


StrikeAbility::StrikeAbility(const string& aSuffix, char aNumber) : AbilityBase(aSuffix, aNumber)
{
	myIconTexturePath = "Data/Textures/Icons/strikeIcon.png";
}

StrikeAbility::~StrikeAbility()
{
}



void StrikeAbility::OnPreCombat(Card* aCard)
{
	aCard;
	if (mySuffix.Lenght() == 0)
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