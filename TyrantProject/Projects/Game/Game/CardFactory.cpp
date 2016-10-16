#include "stdafx.h"
#include "CardFactory.h"
#include "XMLReader.h"

using namespace tinyxml2;

CardFactory* CardFactory::myInstance = nullptr;

CardFactory::CardFactory()
{
}


CardFactory::~CardFactory()
{
}

void CardFactory::Create()
{
	myInstance = new CardFactory();
}

CardFactory & CardFactory::GetInstance()
{
	return *myInstance;
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

void CardFactory::LoadCardData(CardData aCardData, XMLElement* aElement)
{
	aCardData.name = aElement->Attribute("name");
	aCardData.illustrationPath = aElement->Attribute("illustration");
	string faction = aElement->Attribute("faction");
	if (faction == "bloodthirsty")
	{
		aCardData.faction = eCardFaction::BloodThirsty;
	}
	else if (faction == "imperial")
	{
		aCardData.faction = eCardFaction::Imperial;
	}
	else if (faction == "raider")
	{
		aCardData.faction = eCardFaction::Raider;
	}
	else if (faction == "righteous")
	{
		aCardData.faction = eCardFaction::Righteous;
	}
	else if (faction == "xeno")
	{
		aCardData.faction = eCardFaction::Xeno;
	}
	else
	{
		aCardData.faction = eCardFaction::Action;
	}

	string cardType = aElement->Attribute("cardType");

	if (cardType == "assult")
	{
		aCardData.cardType = eCardType::Assult;
	}
	else if (cardType == "structure")
	{
		aCardData.cardType = eCardType::Structure;
	}
	else if (cardType == "action")
	{
		aCardData.cardType = eCardType::Action;
	}
	else
	{
		aCardData.cardType = eCardType::Commander;
	}

	string rarity = aElement->Attribute("rarity");

	if (rarity == "rare")
	{
		aCardData.rarity = eRarity::Rare;
	}
	else if (rarity == "legendary")
	{
		aCardData.rarity = eRarity::Legendary;
	}
	else if (rarity == "uncommon")
	{
		aCardData.rarity = eRarity::Uncommon;
	}
	else
	{
		aCardData.rarity = eRarity::Common;
	}

	aCardData.unique = aElement->BoolAttribute("unique");
	aCardData.cooldown = static_cast<char>(aElement->IntAttribute("cooldown"));
	aCardData.attack = static_cast<char>(aElement->IntAttribute("attack"));
	aCardData.health = static_cast<char>(aElement->IntAttribute("health"));

	myInstance->myCardDatas[aCardData.name.c_str()] = aCardData;
}

void CardFactory::LoadCardsList(const string & anXmlFile)
{
	XMLReader reader;
	reader.OpenDocument(anXmlFile.c_str());

	XMLElement* element = reader.FindFirstChild("root");
	element = element->FirstChildElement();

	CardData card;

	for (XMLElement* element = reader.FindFirstChild("root")->FirstChildElement(); element != nullptr; element = element->NextSiblingElement("card"))
	{
		LoadCardData(card, element);
	}
}

CardData* CardFactory::GetCard(const string aCardName)
{
	if (myInstance->myCardDatas.find(aCardName.c_str()) == myInstance->myCardDatas.end())
	{
		return nullptr;
	}
	return &myInstance->myCardDatas[aCardName.c_str()];
}
