#pragma once
#include "AbilityBase.h"

class FlurryAbility : public AbilityBase
{
public:
	FlurryAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~FlurryAbility();

	void OnCalculateAttack(AttackData& data) override;
};

