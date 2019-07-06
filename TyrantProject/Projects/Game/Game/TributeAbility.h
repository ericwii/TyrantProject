#pragma once
#include "AbilityBase.h"

class TributeAbility : public AbilityBase
{
public:
	TributeAbility();
	~TributeAbility();

	void OnTargeted(Card* aCaster, Card* aTarget, AbilityBase* aTargetingAbility) override;
};

