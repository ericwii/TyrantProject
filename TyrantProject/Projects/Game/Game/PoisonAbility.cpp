#include "stdafx.h"
#include "PoisonAbility.h"


PoisonAbility::PoisonAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/poisonIcon.png";
	myAbilityType = eAbilityTypes::ePoison;
}


PoisonAbility::~PoisonAbility()
{
}

void PoisonAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	aDamagedCard->AddStatusEffect(eStatusEffectType::Poison, iconTexturePath, myNumber);
}
