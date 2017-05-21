#include "stdafx.h"
#include "BerserkAbility.h"


BerserkAbility::BerserkAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix,aNumber,aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/berserkIcon.png";
	myAbilityType = eAbilityTypes::eBerserk;
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
