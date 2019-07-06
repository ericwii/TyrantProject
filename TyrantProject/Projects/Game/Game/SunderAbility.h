#pragma once
#include "AbilityBase.h"

class SunderAbility : public AbilityBase
{
public:
	SunderAbility(CardData& aCardData);
	~SunderAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

