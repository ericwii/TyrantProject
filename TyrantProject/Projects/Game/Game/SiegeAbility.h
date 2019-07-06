#pragma once
#include "AbilityBase.h"

class SiegeAbility: public AbilityBase
{
public:
	SiegeAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~SiegeAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
	void OnCalculateAttack(AttackData& data) override;
	void OnPreCombat(Card* aCard) override;
};

