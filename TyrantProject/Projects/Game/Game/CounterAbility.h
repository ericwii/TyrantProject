#pragma once
#include "AbilityBase.h"

class CounterAbility : public AbilityBase
{
public:
	CounterAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~CounterAbility();

	void OnCombatDamaged(char someDamage, Card* aCard, Card* anAttacker) override;
};

