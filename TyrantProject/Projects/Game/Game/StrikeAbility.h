#pragma once
#include "AbilityBase.h"

class Card;

class StrikeAbility : public AbilityBase
{
public:
	StrikeAbility(const string& aSuffix, char aNumber);
	~StrikeAbility();

	void OnPreCombat(Card* aCard) override;
	void OnAttacked(OnComingAction& anAction) override;

private:

	Card* FindTarget(CU::GrowingArray<Card*>& cards);
};

