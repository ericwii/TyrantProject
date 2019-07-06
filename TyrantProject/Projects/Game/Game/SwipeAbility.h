#pragma once
#include "AbilityBase.h"

class SwipeAbility: public AbilityBase
{
public:
	SwipeAbility(CardData& aCardData);
	~SwipeAbility();

	void OnCalculateAttack(AttackData& data) override;
};

