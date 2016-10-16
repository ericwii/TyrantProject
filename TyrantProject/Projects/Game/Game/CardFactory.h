#pragma once
#include "CardData.h"
#include "XMLReader.h"

using namespace tinyxml2;

class CardFactory
{
public:

	~CardFactory();
	static void Create();
	static CardFactory& GetInstance();
	void LoadCards();
	CardData* GetCard(const string aCardName);


private:
	void LoadCardData(CardData aCardData, XMLElement* aElement);
	void LoadCardsList(const string& anXmlFile);
	static CardFactory* myInstance;
	std::unordered_map<std::string, CardData> myCardDatas;
	CardFactory();
};

