#include "stdafx.h"
#include "DiseaseAbility.h"


DiseaseAbility::DiseaseAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	myAbilityType = eAbilityTypes::eDisease;
	iconTexturePath = "Data/Textures/Icons/Skills/diseaseIcon.png";
	myCardText = "Disease";
}


DiseaseAbility::~DiseaseAbility()
{
}

void DiseaseAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	if (aDamagedCard->GetCardType() != eCardType::Assault)
		return;

	aDamagedCard->AddStatusEffect(eStatusEffectType::Disease);
}
