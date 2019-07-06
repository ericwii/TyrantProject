#include "stdafx.h"
#include "AntiAirAbility.h"


AntiAirAbility::AntiAirAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData): AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/antiAirIcon.png";
	myAbilityType = eAbilityTypes::eAntiAir;
	myCardText.Insert("AntiAir", 0);
}


AntiAirAbility::~AntiAirAbility()
{
}
