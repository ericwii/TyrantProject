#pragma once
#include "AbilityBase.h"

class FearAbility: public AbilityBase
{
public:
	FearAbility();
	~FearAbility();

	void OnBeforeAttack(Card* aCard, Card*& currentTarget, char& someDamage) override;
};

