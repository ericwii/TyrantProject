#include "stdafx.h"
#include "FlurryAbility.h"


FlurryAbility::FlurryAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction):AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/flurryIcon.png";
	myAbilityType = eAbilityTypes::eFlurry;
	myCardText.Insert("Flurry", 0);
}


FlurryAbility::~FlurryAbility()
{
}

void FlurryAbility::OnCalculateAttack(AttackData & data)
{
	if ((rand() % 2) == 1)
	{
		data.amountOfAttacks = myNumber+1;
	}
}
