#include "stdafx.h"
#include "RegenerateAbility.h"


RegenerateAbility::RegenerateAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	myAbilityType = eAbilityTypes::eRegenerate;
	iconTexturePath = "Data/Textures/Icons/Skills/regenerateIcon.png";
	myCardText.Insert("Regenerate", 0);
}


RegenerateAbility::~RegenerateAbility()
{
}

void RegenerateAbility::OnDeath(Card * aCard)
{
	if ((rand() % 2) == 1)
	{
		aCard->Heal(myNumber);
	}
}
