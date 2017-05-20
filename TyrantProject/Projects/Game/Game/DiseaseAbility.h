#pragma once
#include "AbilityBase.h"

class DiseaseAbility: public AbilityBase
{
public:
	DiseaseAbility();
	~DiseaseAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
};

