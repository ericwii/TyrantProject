#pragma once
#include "AbilityBase.h"

class SummonAbility : public AbilityBase
{
public:
	SummonAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~SummonAbility();

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets);
	void OnPreCombat(Card* aCard) override;
	void OnPlay(Card* aCard) override;
	void OnCalculateAttack(AttackData& data) override;
	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker);

private:
	string myCardToSummon;
};

