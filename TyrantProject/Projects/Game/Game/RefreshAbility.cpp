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
	AbilityStack::AddAbility(this, aCard, aCard, 0.2f);
}

void RefreshAbility::DoAction(Card * aCaster, CU::GrowingArray<Card*>& someTargets)
{
	someTargets;

	int heal = 100;
	aCaster->Heal((char)heal);
}
