#pragma once
#include "AbilityBase.h"

class LegionAbility: public AbilityBase
{
public:
	LegionAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~LegionAbility();

	void OnPreCombat(Card* aCard) override;
};

