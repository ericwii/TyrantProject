#pragma once
#include "AbilityBase.h"

class SiphonAbility: public AbilityBase
{
public:
	SiphonAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~SiphonAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

