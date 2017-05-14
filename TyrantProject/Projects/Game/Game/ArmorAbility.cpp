#include "stdafx.h"
#include "ArmorAbility.h"


ArmorAbility::ArmorAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/armoredIcon.png";
}


ArmorAbility::~ArmorAbility()
{
}

void ArmorAbility::OnAttacked(char & someDamage, Card* anAttacker)
{
	someDamage -= myNumber;
}
