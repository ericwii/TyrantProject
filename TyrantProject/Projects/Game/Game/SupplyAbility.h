#pragma once
#include "AbilityBase.h"

class SupplyAbility : public AbilityBase
{
public:
	SupplyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~SupplyAbility();

	void OnCalculateAttack(AttackData& data) override;
	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;


private:
};

