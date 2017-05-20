#include "stdafx.h"
#include "StunAbility.h"


StunAbility::StunAbility()
{
	myAbilityType = eAbilityTypes::eStun;
	iconTexturePath = "Data/Textures/Icons/Skills/stunIcon.png";
}


StunAbility::~StunAbility()
{
}

void StunAbility::OnAttacked(Card * aUser, char & someDamage, Card * anAttacker)
{
	aUser;
	someDamage;
	anAttacker->Stun();
}
