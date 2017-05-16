#pragma once
#include "AbilityBase.h"

class SummonAbility : public AbilityBase
{
public:
	SummonAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~SummonAbility();

	void OnPreCombat(Card* aCard) override;
	void OnPlay(Card* aCard) override;


private:
	string myCardToSummon;
};

