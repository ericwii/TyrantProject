#pragma once
#include "AbilityBase.h"

class AgumentAbility: public AbilityBase
{
public:
	AgumentAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~AgumentAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
	void OnCalculateAttack(AttackData& data) override;
	void OnPreCombat(Card* aCard) override;
	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
};

