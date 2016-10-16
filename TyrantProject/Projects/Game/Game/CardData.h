#pragma once
#include "AbilityBase.h"
#include "stdafx.h"
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
	Assult,
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
	string name;
	string illustrationPath;
	eCardFaction faction;
	eCardType cardType;
	eRarity rarity;
	CU::VectorOnStack<AbilityBase*, 3> abilitys;
	bool unique;
	char cooldown;
	char attack;
	char health;
};