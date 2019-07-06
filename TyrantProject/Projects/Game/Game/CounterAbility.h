#pragma once
#include "AbilityBase.h"

class CounterAbility : public AbilityBase
{
public:
	CounterAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~CounterAbility();

	void OnCombatDamaged(char someDamage, Card* aCard, Card* anAttacker) override;
};

