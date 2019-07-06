#pragma once
#include "AbilityBase.h"

class ArmorAbility: public AbilityBase
{
public:
	ArmorAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~ArmorAbility();

	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
};

