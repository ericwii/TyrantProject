#pragma once
#include "AbilityBase.h"

class DiseaseAbility: public AbilityBase
{
public:
	DiseaseAbility(CardData& aCardData);
	~DiseaseAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

