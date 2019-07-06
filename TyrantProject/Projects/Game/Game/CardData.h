#pragma once
#include "../../CommonUtilities/VectorOnStack.h"

class AbilityBase;

enum eCardFaction
{
	BloodThirsty,
	Imperial,
	Raider,
	Righteous,
	Xeno,
	Action,
	NumberofFactions
};

enum class eCardType
{
	Structure,
	Commander,
	Assault,
	Action
};

enum class eRarity
{
	Common,
	Uncommon,
	Rare,
	Legendary
};



struct CardData
{
	string name = "none";
	string illustrationPath = "none";
	eCardFaction faction = eCardFaction::NumberofFactions;
	eCardType cardType = eCardType::Action;
	eRarity rarity = eRarity::Common;
	CU::VectorOnStack<AbilityBase*, 3> abilities;
	bool unique = false;
	char cooldown = 0;
	char attack = 1;
	short health = 1;
};