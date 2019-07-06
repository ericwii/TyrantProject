#pragma once
#include "AbilityBase.h"

class RefreshAbility : public AbilityBase
{
public:
	RefreshAbility(CardData& aCardData);
	~RefreshAbility();


	void OnCleanUp(Card* aCard) override;
};

