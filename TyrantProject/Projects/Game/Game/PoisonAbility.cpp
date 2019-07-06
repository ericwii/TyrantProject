#include "stdafx.h"
#include "PoisonAbility.h"


PoisonAbility::PoisonAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData): AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/poisonIcon.png";
	myAbilityType = eAbilityTypes::ePoison;
	myCardText.Insert("Poison", 0);
}


PoisonAbility::~PoisonAbility()
{
}

void PoisonAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	if (aDamagedCard->GetCardType() != eCardType::Assault)
		return;

	aDamagedCard->AddStatusEffect(eStatusEffectType::Poison, iconTexturePath, myNumber);
}
