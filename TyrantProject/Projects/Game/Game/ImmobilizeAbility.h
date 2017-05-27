#pragma once
#include "AbilityBase.h"

class ImmobilizeAbility: public AbilityBase
{
public:
	ImmobilizeAbility();
	~ImmobilizeAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

