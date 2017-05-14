#pragma once
#include "AbilityBase.h"

class ArmorAbility: public AbilityBase
{
public:
	ArmorAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~ArmorAbility();

	void OnAttacked(char& someDamage, Card* anAttacker) override;
};

