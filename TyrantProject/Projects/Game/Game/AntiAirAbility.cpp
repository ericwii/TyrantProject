#include "stdafx.h"
#include "AntiAirAbility.h"


AntiAirAbility::AntiAirAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/antiAirIcon.png";
	myAbilityType = eAbilityTypes::eAntiAir;
	myCardText.Insert("AntiAir", 0);
}


AntiAirAbility::~AntiAirAbility()
{
}
