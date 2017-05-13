#pragma once
#include "AbilityBase.h"

class RefreshAbility : public AbilityBase
{
public:
	RefreshAbility();
	~RefreshAbility();


	void OnCleanUp(Card* aCard) override;

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
};

