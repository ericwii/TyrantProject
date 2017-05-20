#include "stdafx.h"
#include "ImmobiliseAbility.h"


ImmobiliseAbility::ImmobiliseAbility()
{
	myAbilityType = eAbilityTypes::eImmobilise;
	iconTexturePath = "Data/Textures/Icons/Skills/immobilizeIcon.png";
}


ImmobiliseAbility::~ImmobiliseAbility()
{
}

void ImmobiliseAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	if ((rand() % 2) == 1)
	{
		aDamagedCard->Immobilize();
	}
}
