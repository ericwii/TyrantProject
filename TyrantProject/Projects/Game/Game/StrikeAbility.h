#pragma once
#include "AbilityBase.h"


class StrikeAbility : public AbilityBase
{
public:
	StrikeAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~StrikeAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;
	void OnCalculateAttack(AttackData& data) override;
	void OnPreCombat(Card* aCard) override;
	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker) override;
	void OnPlay(Card* aCard) override;

private:
};

