#pragma once
#include "AbilityBase.h"

class PierceAbility: public AbilityBase
{
public:
	PierceAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~PierceAbility();


};

