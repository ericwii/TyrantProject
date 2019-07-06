#include "stdafx.h"
#include "PierceAbility.h"


PierceAbility::PierceAbility(const string & aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData): AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/pierceIcon.png";
	myAbilityType = eAbilityTypes::ePierce;
	myCardText.Insert("Pierce", 0);
}

PierceAbility::~PierceAbility()
{
}
