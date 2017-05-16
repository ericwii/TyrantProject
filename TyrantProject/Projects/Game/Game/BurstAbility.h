#pragma once
#include "AbilityBase.h"

class BurstAbility: public AbilityBase
{
public:
	BurstAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction);
	~BurstAbility();


};

