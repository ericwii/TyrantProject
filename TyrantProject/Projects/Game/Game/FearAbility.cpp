#include "stdafx.h"
#include "FearAbility.h"


FearAbility::FearAbility(CardData& aCardData) : AbilityBase(aCardData)
{
	iconTexturePath = "Data/Textures/Icons/Skills/fearIcon.png";
	myAbilityType = eAbilityTypes::eFear;
	myCardText = "Fear";
}


FearAbility::~FearAbility()
{
}

void FearAbility::OnCalculateAttack(AttackData& data) 
{
	data.mainTarget = data.mainTarget->GetOwner()->GetCommander();
}
