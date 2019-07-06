#pragma once
#include "AbilityBase.h"

class BerserkAbility : public AbilityBase
{
public:
	BerserkAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~BerserkAbility();

	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage) override;
	void OnCombatDamaged(char someDamage, Card* aCard, Card* anAttacker) override;
	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
};

