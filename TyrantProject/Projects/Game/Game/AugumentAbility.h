#pragma once
#include "AbilityBase.h"

class AugmentAbility: public AbilityBase
{
public:
	AugmentAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~AugmentAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
	void OnCalculateAttack(AttackData& data) override;
	void OnPreCombat(Card* aCard) override;
	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
};

