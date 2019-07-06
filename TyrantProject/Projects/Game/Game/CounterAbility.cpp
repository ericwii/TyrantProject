#include "stdafx.h"
#include "CounterAbility.h"


CounterAbility::CounterAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData) : AbilityBase(aSuffix, aNumber, aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/counterIcon.png";
	myAbilityType = eAbilityTypes::eCounter;
	myCardText.Insert("Counter", 0);
}

CounterAbility::~CounterAbility()
{
}


void CounterAbility::OnCombatDamaged(char someDamage, Card* aCard, Card* anAttacker)
{
	aCard;
	someDamage;
	anAttacker->TakeDamage(myNumber);
}