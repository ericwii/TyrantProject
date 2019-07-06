#include "stdafx.h"
#include "PhaseAbility.h"


PhaseAbility::PhaseAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/phaseIcon.png";
	myAbilityType = eAbilityTypes::ePhase;
	myCardText.Insert("Phase", 0);
}


PhaseAbility::~PhaseAbility()
{
}


void PhaseAbility::OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage)
{
	aCard;
	someDamage;

	if (aDamagedCard->GetCardType() != eCardType::Assault)
		return;

	aDamagedCard->AddStatusEffect(eStatusEffectType::Phase);
}
