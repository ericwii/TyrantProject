#pragma once
#include "AbilityBase.h"

class JamAbility: public AbilityBase
{
public:
	JamAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~JamAbility();

	void OnCalculateAttack(AttackData& data) override;

	void DoAction(Card* aCaster, CU::GrowingArray<Card*>& someTargets) override;

	void OnPreCombat(Card* aCard) override;

	void OnPlay(Card* aCard) override;
};

