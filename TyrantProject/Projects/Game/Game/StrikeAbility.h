#pragma once
#include "AbilityBase.h"

class StrikeAbility : public AbilityBase
{
public:
	StrikeAbility(const string& aSuffix, char aNumber);
	~StrikeAbility();

	void OnPreCombat(Card* aCard) override;
	void OnAttacked(OnComingAction& anAction) override;
};

