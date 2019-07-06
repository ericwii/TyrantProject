#include "stdafx.h"
#include "BerserkAbility.h"


BerserkAbility::BerserkAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData): AbilityBase(aSuffix,aNumber,aSpecificFaction, aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/berserkIcon.png";
	myAbilityType = eAbilityTypes::eBerserk;
	myCardText.Insert("Berserk", 0);
}


BerserkAbility::~BerserkAbility()
{
}

void BerserkAbility::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	if (mySuffix == "")
	{
		someDamage;
		aDamagedCard;
		aCard->Berserk(myNumber);
	}
}

void BerserkAbility::OnCombatDamaged(char someDamage, Card * aCard, Card * anAttacker)
{
	someDamage;
	aCard;
	anAttacker;
}

void BerserkAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	if (mySuffix == "onattacked")
	{
		someDamage;
		anAttacker;
		aUser->Berserk(myNumber);
	}
}
