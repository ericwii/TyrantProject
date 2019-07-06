#include "stdafx.h"
#include "SunderAbility.h"


SunderAbility::SunderAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/sunderIcon.png";
	myAbilityType = eAbilityTypes::eSunder;
	myCardText.Insert("Sunder", 0);
}


SunderAbility::~SunderAbility()
{
}


void SunderAbility::OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	if (aDamagedCard->GetCardType() != eCardType::Assault)
		return;

	aDamagedCard->AddStatusEffect(eStatusEffectType::Sunder);
}