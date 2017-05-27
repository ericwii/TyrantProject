#include "stdafx.h"
#include "LeechAbility.h"


LeechAbility::LeechAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction) : AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/leechIcon.png";
	myAbilityType = eAbilityTypes::eLeech;
	myCardText.Insert("Leech", 0);
}


LeechAbility::~LeechAbility()
{
}

void LeechAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aDamagedCard;
	someDamage;

	if (aCard->IsDying() == false && aCard->IsAtMaxHealth() == false)
	{
		aCard->Heal(myNumber);
	}
}
