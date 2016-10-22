#include "stdafx.h"
#include "CardFactory.h"

using namespace tinyxml2;

CardFactory* CardFactory::myInstance = nullptr;

string illustrationStartPath = "Data/Textures/Illustrations/";


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
		LoadCardsList(element->Attribute("commanderPath"));
	}

	/*rootelement = rootelement->NextSiblingElement("ActionCardList");
	LoadCardsList(rootelement->Attribute("actionsPath"));*/

}

CardData* CardFactory::GetCard(const string& aCardName)
{
	if (myInstance->myCardDatas.find(aCardName.c_str()) == myInstance->myCardDatas.end())
	{
		DEBUG_ASSERT(false, "Failed to get card from CardFactory");
		return nullptr;
	}
	return &myInstance->myCardDatas[aCardName.c_str()];
}

CU::VectorOnStack<CardData*, DECK_MAX_SIZE> CardFactory::GetDeck(const string& anXmlFile)
{
	CU::VectorOnStack<CardData*, DECK_MAX_SIZE> deckToReturn;

	XMLReader reader;
	reader.OpenDocument(anXmlFile.c_str());

	XMLElement* element = reader.FindFirstChild("root");
	element = element->FirstChildElement();

	XMLElement* commanderElement = element->FirstChildElement("commander");
	DEBUG_ASSERT(commanderElement != nullptr, "No commander found for card deck");

	deckToReturn.Add(GetCard(commanderElement->Attribute("name")));

	element = element->FirstChildElement("card");
	for (; element != nullptr; element = element->NextSiblingElement("card"))
	{
		deckToReturn.Add(GetCard(element->Attribute("name")));
	}

	return deckToReturn;
}





//Private methods

void CardFactory::LoadCardData(XMLElement* aElement)
{
	CardData aCardData;

	aCardData.name = aElement->Attribute("name");
	aCardData.illustrationPath = illustrationStartPath + aElement->Attribute("illustration");

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
	if (cardType == "assault")
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
	aCardData.health = static_cast<char>(aElement->IntAttribute("health"));

	if (aCardData.cardType == eCardType::Assult || aCardData.cardType == eCardType::Structure)
	{
		aCardData.cooldown = static_cast<char>(aElement->IntAttribute("cooldown"));
	}
	if (aCardData.cardType == eCardType::Assult)
	{
		aCardData.attack = static_cast<char>(aElement->IntAttribute("attack"));
	}

	myInstance->myCardDatas[aCardData.name.c_str()] = aCardData;
}

void CardFactory::LoadCardsList(const string & anXmlFile)
{
	XMLReader reader;
	reader.OpenDocument(anXmlFile.c_str());

	XMLElement* element = reader.FindFirstChild("root");
	element = element->FirstChildElement();

	for (; element != nullptr; element = element->NextSiblingElement("card"))
	{
		LoadCardData(element);
	}
}
