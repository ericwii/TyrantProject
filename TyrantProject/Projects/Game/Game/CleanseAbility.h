#pragma once
#include "AbilityBase.h"

class CleanseAbility: public AbilityBase
{
public:
	CleanseAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~CleanseAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
	void OnCalculateAttack(AttackData& data) override;
	void OnPreCombat(Card* aCard) override;
	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
};

