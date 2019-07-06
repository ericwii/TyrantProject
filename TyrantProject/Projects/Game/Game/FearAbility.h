#pragma once
#include "AbilityBase.h"

class FearAbility: public AbilityBase
{
public:
	FearAbility(CardData& aCardData);
	~FearAbility();

	void OnCalculateAttack(AttackData& data) override;
};

