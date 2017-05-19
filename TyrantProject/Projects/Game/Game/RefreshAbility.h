#pragma once
#include "AbilityBase.h"

class RefreshAbility : public AbilityBase
{
public:
	RefreshAbility();
	~RefreshAbility();


	void OnCleanUp(Card* aCard) override;
};

