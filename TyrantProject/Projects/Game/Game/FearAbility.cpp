#include "stdafx.h"
#include "FearAbility.h"


FearAbility::FearAbility()
{
	iconTexturePath = "Data/Textures/Icons/Skills/fearIcon.png";
	myAbilityType = eAbilityTypes::eFear;
}


FearAbility::~FearAbility()
{
}

void FearAbility::OnBeforeAttack(Card * aCard, Card *& currentTarget, char & someDamage)
{
	currentTarget = aCard->GetOwner()->GetOpponent()->GetCommander();
	someDamage;
}
