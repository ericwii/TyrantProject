#pragma once
#include "AbilityBase.h"

class AntiAirAbility: public AbilityBase
{
public:
	AntiAirAbility(const string& aSuffix, char aNumber, eCardFaction aSpecificFaction, CardData& aCardData);
	~AntiAirAbility();


};

