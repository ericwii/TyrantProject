#pragma once
#include "AbilityBase.h"

class SupplyAbility : public AbilityBase
{
public:
	SupplyAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~SupplyAbility();

	void OnBeforeAttack(Card* aCard, Card*& currentTarget, char& someDamage) override;
	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;


private:
};

