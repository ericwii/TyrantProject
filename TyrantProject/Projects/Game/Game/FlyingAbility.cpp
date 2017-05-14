#include "stdafx.h"
#include "FlyingAbility.h"


FlyingAbility::FlyingAbility()
{
	iconTexturePath = "Data/Textures/Icons/Skills/flyingIcon.png";
	myAbilityType = eAbilityTypes::eFlying;
}


FlyingAbility::~FlyingAbility()
{
}

void FlyingAbility::OnAttacked(char & someDamage, Card * anAttacker)
{
	for (int i = 0; i < anAttacker->GetAbilities().Size(); i++)
	{
		if (anAttacker->GetAbilities()[i]->GetAbilityType() == eAbilityTypes::eAntiAir)
		{
			someDamage += anAttacker->GetAbilities()[i]->GetNumber();
			return;
		}
		else if(anAttacker->GetAbilities()[i]->GetAbilityType() == eAbilityTypes::eFlying)
		{
			return;
		}
	}

	if ((rand() % 2) == 1)
	{
		someDamage = 0;
	}
}
