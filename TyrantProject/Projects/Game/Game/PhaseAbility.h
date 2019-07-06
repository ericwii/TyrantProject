#pragma once
#include "AbilityBase.h"

class PhaseAbility : public AbilityBase
{
public:
	PhaseAbility(CardData& aCardData);
	~PhaseAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

