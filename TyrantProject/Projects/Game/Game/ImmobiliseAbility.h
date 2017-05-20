#pragma once
#include "AbilityBase.h"

class ImmobiliseAbility: public AbilityBase
{
public:
	ImmobiliseAbility();
	~ImmobiliseAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

