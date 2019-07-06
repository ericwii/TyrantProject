#pragma once
#include "AbilityBase.h"

class FlyingAbility: public AbilityBase
{
public:
	FlyingAbility(CardData& aCardData);
	~FlyingAbility();

	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
};

