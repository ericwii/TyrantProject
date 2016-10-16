#include "stdafx.h"
#include "CardFactory.h"
#include "XMLReader.h"

using namespace tinyxml2;

CardFactory::CardFactory()
{
}


CardFactory::~CardFactory()
{
}

void CardFactory::LoadCards()
{
	if ()
	{

	}

	XMLReader reader;
	reader.OpenDocument(anXmlFile.c_str());

	XMLElement* element = reader.FindFirstChild("root");
	element = element->FirstChildElement();

	CardData card;

	card.name = element->Attribute("name");
	if (element->Attribute("faction") == "Bloodthirsty")
	{
		card.faction = eCardFaction::BloodThirsty;
	}
	else if (element->Attribute("faction") == "Raider")
	{
		card.faction = eCardFaction::Raider;
	}
	else if (element->Attribute("faction") == "Righteous")
	{
		card.faction = eCardFaction::Righteous;
	}
	else if (element->Attribute("faction") == "Xeno")
	{
		card.faction = eCardFaction::Xeno;
	}
	else
	{
		card.faction = eCardFaction::Imperial;
	}


	if (element->Attribute("cardType") == "Assult")
	{
		card.cardType = eCardType::Assult;
	}
	if (element->Attribute("cardType") == "Structure")
	{
		card.cardType = eCardType::Structure;
	}
	if (element->Attribute("cardType") == "Action")
	{
		card.cardType = eCardType::Action;
	}
	else
	{
		card.cardType = eCardType::Commander;
	}

	if (element->Attribute("rarity") == "Rare")
	{
		card.rarity = eRarity::Rare;
	}
	if (element->Attribute("rarity") == "Legendary")
	{
		card.rarity = eRarity::Legendary;
	}
	if (element->Attribute("rarity") == "Uncommon")
	{
		card.rarity = eRarity::Uncommon;
	}
	else
	{
		card.rarity = eRarity::Common;
	}

	card.unique = element->Attribute("unique");
	card.cooldown = element->IntAttribute("cooldown");
	card.attack = element->IntAttribute("attack");
	card.health = element->IntAttribute("health");
}
