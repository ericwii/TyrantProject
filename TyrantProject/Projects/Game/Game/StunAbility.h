#pragma once
#include "AbilityBase.h"

class StunAbility: public AbilityBase
{
public:
	StunAbility(CardData& aCardData);
	~StunAbility();

	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
};

