#pragma once
#include "AbilityBase.h"

class WeakenAbility : public AbilityBase
{
public:
	WeakenAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~WeakenAbility();

	void OnPreCombat(Card* aCard) override;

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
};

