#pragma once
#include "AbilityBase.h"

class WallAbility: public AbilityBase
{
public:
	WallAbility(CardData& aCardData);
	~WallAbility();

	void OnCommanderAttack(Card*& aCurrentTarget, Card* aUser) override;
	//void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets);
};

