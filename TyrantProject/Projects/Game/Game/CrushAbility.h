#pragma once
#include "AbilityBase.h"

class CrushAbility: public AbilityBase
{
public:
	CrushAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~CrushAbility();

	void OnKill(Card* aCard, Card* aKilledCard) override;
};

