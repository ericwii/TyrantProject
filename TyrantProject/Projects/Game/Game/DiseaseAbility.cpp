#include "stdafx.h"
#include "DiseaseAbility.h"


DiseaseAbility::DiseaseAbility()
{
	myAbilityType = eAbilityTypes::eDisease;
	iconTexturePath = "Data/Textures/Icons/Skills/diseaseIcon.png";
}


DiseaseAbility::~DiseaseAbility()
{
}

void DiseaseAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	aDamagedCard->Disease();
}
