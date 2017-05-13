#pragma once
#include "AbilityBase.h"


class HealAbility : public AbilityBase
{
public:
	HealAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~HealAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;

	void OnPreCombat(Card* aCard) override;
};

