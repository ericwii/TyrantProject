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

void FearAbility::OnCalculateAttack(AttackData& data) 
{
	data.mainTarget = data.mainTarget->GetOwner()->GetCommander();
}
