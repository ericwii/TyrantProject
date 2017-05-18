#pragma once
#include "AbilityBase.h"

class FearAbility: public AbilityBase
{
public:
	FearAbility();
	~FearAbility();

	void OnCalculateAttack(AttackData& data) override;
};

