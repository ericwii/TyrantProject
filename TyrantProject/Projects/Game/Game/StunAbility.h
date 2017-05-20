#pragma once
#include "AbilityBase.h"

class StunAbility: public AbilityBase
{
public:
	StunAbility();
	~StunAbility();

	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
};

