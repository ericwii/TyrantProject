#include "stdafx.h"
#include "RefreshAbility.h"


RefreshAbility::RefreshAbility()
{
	iconTexturePath = "Data/Textures/Icons/Skills/refreshIcon.png";
}


RefreshAbility::~RefreshAbility()
{
}

void RefreshAbility::OnCleanUp(Card * aCard)
{
	
	AbilityStack::AddAbility(this, aCard, aCard,0.20f);
}

void RefreshAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	aCaster->Heal(10000);
}
