#pragma once
#include "AbilityBase.h"

class LegionAbility: public AbilityBase
{
public:
	LegionAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~LegionAbility();

	void OnPreCombat(Card* aCard) override;
};

