#pragma once
#include "AbilityBase.h"

class FlyingAbility: public AbilityBase
{
public:
	FlyingAbility();
	~FlyingAbility();

	void OnAttacked(char& someDamage, Card* anAttacker) override;
};

