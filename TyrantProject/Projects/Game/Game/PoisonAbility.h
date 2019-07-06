#pragma once
#include "AbilityBase.h"

class PoisonAbility: public AbilityBase
{
public:
	PoisonAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~PoisonAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

