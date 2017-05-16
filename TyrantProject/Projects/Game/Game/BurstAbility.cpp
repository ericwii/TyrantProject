#include "stdafx.h"
#include "BurstAbility.h"


BurstAbility::BurstAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/burstIcon.png";
	myAbilityType = eAbilityTypes::eBurst;
}


BurstAbility::~BurstAbility()
{
}
