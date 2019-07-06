#pragma once
#include "CardData.h"


#define DECK_MAX_SIZE 20

namespace tinyxml2
{
	class XMLElement;
}

class CardFactory
{
public:

	~CardFactory();
	static void Create();
	static CardFactory& GetInstance();
	void LoadCards();
	CardData* GetCard(const string& aCardName);

	CU::VectorOnStack<CardData*, DECK_MAX_SIZE> GetDeck(const string& anXmlFile);

	void operator=(const CardFactory&) = delete;

private:
	void LoadCardData(tinyxml2::XMLElement* aElement);
	void LoadCardsList(const string& anXmlFile);
	void LoadCardAbilities(CardData& someData, tinyxml2::XMLElement* aCardElement);

	AbilityBase* GetAbility(const string& aName, const string& aSuffix, char aNumber, eCardFaction aFaction, CardData& aCardData);
	eCardFaction GetFactionFromString(string& aString);

	const char* ReadStringElement(tinyxml2::XMLElement* aElement);
	int ReadIntElement(tinyxml2::XMLElement* aElement);
	bool ReadBoolElement(tinyxml2::XMLElement* aElement);

	static CardFactory* myInstance;
	std::unordered_map<std::string, CardData> myCardDatas;
	CardFactory();
};

