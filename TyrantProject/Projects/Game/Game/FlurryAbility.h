#pragma once
#include "AbilityBase.h"

class FlurryAbility : public AbilityBase
{
public:
	FlurryAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~FlurryAbility();

	void OnCalculateAttack(AttackData& data) override;
};

