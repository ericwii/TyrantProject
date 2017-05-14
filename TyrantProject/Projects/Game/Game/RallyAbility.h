#pragma once
#include "AbilityBase.h" 

class RallyAbility : public AbilityBase
{
public:
	RallyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~RallyAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;

	void OnPreCombat(Card* aCard) override;
};

