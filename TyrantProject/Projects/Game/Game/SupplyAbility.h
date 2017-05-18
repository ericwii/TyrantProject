#pragma once
#include "AbilityBase.h"

class SupplyAbility : public AbilityBase
{
public:
	SupplyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~SupplyAbility();

	void OnPreCombat(Card* aCard) override;
	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
};

