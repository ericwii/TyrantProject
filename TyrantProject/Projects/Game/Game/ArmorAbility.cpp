#include "stdafx.h"
#include "ArmorAbility.h"


ArmorAbility::ArmorAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction): AbilityBase(aSuffix, aNumber, aSpecificFaction)
{
	iconTexturePath = "Data/Textures/Icons/Skills/armoredIcon.png";
	myAbilityType = eAbilityTypes::eArmor;
}


ArmorAbility::~ArmorAbility()
{
}

void ArmorAbility::OnAttacked(char & someDamage, Card* anAttacker)
{
	char reductionReduction = 0;
	char damageReduction = myNumber;


	for (short i = 0; i < anAttacker->GetAbilities().Size(); i++)
	{
		if(anAttacker->GetAbilities()[i]->GetAbilityType() == eAbilityTypes::ePierce)
		{
			reductionReduction += anAttacker->GetAbilities()[i]->GetNumber();
		}
	}

	damageReduction -= reductionReduction;

	if (damageReduction < 0)
	{
		damageReduction = 0;
	}

	someDamage -= damageReduction;

	if (someDamage < 0)
	{
		someDamage = 0;
	}
}
