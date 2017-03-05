#pragma once
#include "AbilityBase.h"

class Card;

class StrikeAbility : public AbilityBase
{
public:
	StrikeAbility(const string& aSuffix, char aNumber);
	~StrikeAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;

	void OnPreCombat(Card* aCard) override;
	void OnAttacked(char& someDamage) override;

private:

	Card* FindTarget(CU::GrowingArray<Card*>& cards);
};

