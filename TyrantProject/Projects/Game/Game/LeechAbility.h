#pragma once
#include "AbilityBase.h"

class LeechAbility: public AbilityBase
{
public:
	LeechAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~LeechAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

