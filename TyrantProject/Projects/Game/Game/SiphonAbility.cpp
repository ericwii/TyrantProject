#include "stdafx.h"
#include "SiphonAbility.h"


SiphonAbility::SiphonAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/siphonIcon.png";
	myAbilityType = eAbilityTypes::eSiphon;
}


SiphonAbility::~SiphonAbility()
{
}

void SiphonAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aDamagedCard;
	someDamage;

	if (aCard->GetOwner()->GetCommander()->IsAtMaxHealth() == false)
	{
		aCard->GetOwner()->GetCommander()->Heal(myNumber);
	}
}