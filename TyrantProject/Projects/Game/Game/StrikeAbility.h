#pragma once
#include "AbilityBase.h"


class StrikeAbility : public AbilityBase
{
public:
	StrikeAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~StrikeAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
	void OnBeforeAttack(Card* aCard, Card*& currentTarget, char& someDamage) override;
	void OnPreCombat(Card* aCard) override;

private:
};

