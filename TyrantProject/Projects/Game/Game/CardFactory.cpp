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
	

	XMLReader reader;
	reader.OpenDocument("Data/XML files/cardFiles.xml");

	XMLElement* rootelement = reader.FindFirstChild("root");
	rootelement = rootelement->FirstChildElement();

	for (XMLElement* element = reader.FindFirstChild("root")->FirstChildElement(); element != nullptr; element = element->NextSiblingElement("CardList"))
	{
		LoadCardsList(element->Attribute("structuresPath"));
		LoadCardsList(element->Attribute("assultPath"));
		//LoadCardsList(element->Attribute("commanderPath")); // missing xml files for commanders
	}

	/*rootelement = rootelement->NextSiblingElement("ActionCardList");
	LoadCardsList(rootelement->Attribute("actionsPath"));*/

}

void CardFactory::LoadCardsList(const string & anXmlFile)
{
	XMLReader reader;
	reader.OpenDocument(anXmlFile.c_str());

	XMLElement* element = reader.FindFirstChild("root");
	element = element->FirstChildElement();

	CardData card;

	card.name = element->Attribute("name");
	string faction = element->Attribute("faction");
	if (faction == "bloodthirsty")
	{
		card.faction = eCardFaction::BloodThirsty;
	}
	else if (faction == "imperial")
	{
		card.faction = eCardFaction::Imperial;
	}
	else if (faction == "raider")
	{
		card.faction = eCardFaction::Raider;
	}
	else if (faction == "righteous")
	{
		card.faction = eCardFaction::Righteous;
	}
	else if (faction == "xeno")
	{
		card.faction = eCardFaction::Xeno;
	}
	else
	{
		card.faction = eCardFaction::Action;
	}

	string cardType = element->Attribute("cardType");

	if (cardType == "assult")
	{
		card.cardType = eCardType::Assult;
	}
	else if (cardType == "structure")
	{
		card.cardType = eCardType::Structure;
	}
	else if (cardType == "action")
	{
		card.cardType = eCardType::Action;
	}
	else
	{
		card.cardType = eCardType::Commander;
	}

	string rarity = element->Attribute("rarity");

	if (rarity == "rare")
	{
		card.rarity = eRarity::Rare;
	}
	else if (rarity == "legendary")
	{
		card.rarity = eRarity::Legendary;
	}
	else if (rarity == "uncommon")
	{
		card.rarity = eRarity::Uncommon;
	}
	else
	{
		card.rarity = eRarity::Common;
	}

	card.unique = element->BoolAttribute("unique");
	card.cooldown = static_cast<char>(element->IntAttribute("cooldown"));
	card.attack = static_cast<char>(element->IntAttribute("attack"));
	card.health = static_cast<char>(element->IntAttribute("health"));

	myCardDatas[card.name.c_str()] = card;
}

CardData & CardFactory::GetCard(const string aCardName)
{
	return myCardDatas[aCardName.c_str()];
}
