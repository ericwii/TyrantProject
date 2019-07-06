#pragma once
#include "AbilityBase.h"

class EnfeebleAbility: public AbilityBase
{
public:
	EnfeebleAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~EnfeebleAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
	void OnCalculateAttack(AttackData& data) override;
	void OnPreCombat(Card* aCard) override;
};

