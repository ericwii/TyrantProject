#pragma once
#include "AbilityBase.h"

class SiegeAbility: public AbilityBase
{
public:
	SiegeAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~SiegeAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;

	void OnPreCombat(Card* aCard) override;
};

