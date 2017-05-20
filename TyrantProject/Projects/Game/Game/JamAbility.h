#pragma once
#include "AbilityBase.h"

class JamAbility: public AbilityBase
{
public:
	JamAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~JamAbility();

	void OnCalculateAttack(AttackData& data) override;

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;

	void OnPreCombat(Card* aCard) override;
};

