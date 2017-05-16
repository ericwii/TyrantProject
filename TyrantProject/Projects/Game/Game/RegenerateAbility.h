#pragma once
#include "AbilityBase.h"

class RegenerateAbility: public AbilityBase
{
public:
	RegenerateAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~RegenerateAbility();

	void OnDeath(Card* aCard) override;
};

