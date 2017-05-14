#include "stdafx.h"
#include "CardFactory.h"
#include "AllAbilities.h"

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

	aCardData.name = ReadStringElement(aElement->FirstChildElement("name"));
	aCardData.illustrationPath = illustrationStartPath + ReadStringElement(aElement->FirstChildElement("illustration"));

	string faction = ReadStringElement(aElement->FirstChildElement("faction"));
	aCardData.faction = GetFactionFromString(faction);
	
	string cardType = ReadStringElement(aElement->FirstChildElement("cardType"));
	if (cardType == "assault")
	{
		aCardData.cardType = eCardType::Assault;
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
	
	string rarity = ReadStringElement(aElement->FirstChildElement("rarity"));
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
	
	aCardData.unique = ReadBoolElement(aElement->FirstChildElement("unique"));
	aCardData.health = static_cast<char>(ReadIntElement(aElement->FirstChildElement("health")));
	
	if (aCardData.cardType == eCardType::Assault || aCardData.cardType == eCardType::Structure)
	{
		aCardData.cooldown = static_cast<char>(ReadIntElement(aElement->FirstChildElement("cooldown")));
	}
	if (aCardData.cardType == eCardType::Assault)
	{
		aCardData.attack = static_cast<char>(ReadIntElement(aElement->FirstChildElement("attack")));
	}

	LoadCardAbilities(aCardData, aElement);

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

void CardFactory::LoadCardAbilities(CardData& someData, tinyxml2::XMLElement* aCardElement)
{
	XMLElement* currentElement = aCardElement->FirstChildElement("skill");

	string currentName;
	string currentSuffix;
	string currentFactionString;
	AbilityBase* currentAbility;
	char currentNumber = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (currentElement != nullptr)
		{
			currentName = currentElement->Attribute("name");
			if (currentElement->Attribute("number") != nullptr)
			{
				currentNumber = static_cast<char>(currentElement->IntAttribute("number"));
			}
			if (currentElement->Attribute("suffix") != nullptr)
			{
				currentSuffix = currentElement->Attribute("suffix");
			}
			if (currentElement->Attribute("faction") != nullptr)
			{
				currentFactionString = currentElement->Attribute("suffix");
				currentAbility = GetAbility(currentName, currentSuffix, currentNumber, GetFactionFromString(currentFactionString));
			}
			else
			{
				currentAbility = GetAbility(currentName, currentSuffix, currentNumber, eCardFaction::Action);
			}

			if (currentAbility != nullptr)
			{
				someData.abilities.Add(currentAbility);
			}
			currentElement = currentElement->NextSiblingElement("skill");
			currentSuffix = "";
			currentNumber = 0;
		}
	}
}

AbilityBase* CardFactory::GetAbility(const string& aName, const string& aSuffix, char aNumber, eCardFaction aFaction)
{
	if (aName == "strike")
	{
		return new StrikeAbility(aSuffix, aNumber, aFaction);
	}
	else if (aName == "heal")
	{
		return new HealAbility(aSuffix, aNumber, aFaction);
	}
	else if (aName == "refresh")
	{
		return new RefreshAbility();
	}
	else if (aName == "siege")
	{
		return new SiegeAbility(aSuffix, aNumber, aFaction);
	}
	else if (aName == "wall")
	{
		return new WallAbility();
	}

	return nullptr;
}

eCardFaction CardFactory::GetFactionFromString(string& aString)
{
	if (aString == "bloodthirsty")
	{
		return eCardFaction::BloodThirsty;
	}
	else if (aString == "imperial")
	{
		return eCardFaction::BloodThirsty;
	}
	else if (aString == "raider")
	{
		return eCardFaction::BloodThirsty;
	}
	else if (aString == "righteous")
	{
		return eCardFaction::BloodThirsty;
	}
	else if (aString == "xeno")
	{
		return eCardFaction::BloodThirsty;
	}

	return eCardFaction::Action;
}



const char* CardFactory::ReadStringElement(tinyxml2::XMLElement* aElement)
{
	return aElement->FirstChild()->Value();
}

int CardFactory::ReadIntElement(tinyxml2::XMLElement* aElement)
{
	const char* intString = aElement->FirstChild()->Value();
	return std::stoi(intString);
}

bool CardFactory::ReadBoolElement(tinyxml2::XMLElement* aElement)
{
	string boolString = aElement->FirstChild()->Value();
	return boolString == "true";
}
