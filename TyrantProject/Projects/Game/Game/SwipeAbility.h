#pragma once
#include "AbilityBase.h"

class SwipeAbility: public AbilityBase
{
public:
	SwipeAbility();
	~SwipeAbility();

	void OnCalculateAttack(AttackData& data) override;
};

