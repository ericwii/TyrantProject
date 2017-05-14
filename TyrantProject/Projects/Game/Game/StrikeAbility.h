#pragma once
#include "AbilityBase.h"


class StrikeAbility : public AbilityBase
{
public:
	StrikeAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~StrikeAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;

	void OnPreCombat(Card* aCard) override;
	void OnAttacked(char& someDamage) override;

private:
};
