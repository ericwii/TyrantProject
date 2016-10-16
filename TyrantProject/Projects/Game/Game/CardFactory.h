#pragma once
#include "CardData.h"
class CardFactory
{
public:

	~CardFactory();
	static void Create();
	static CardFactory& GetInstance();
	static void LoadCards();
	static void LoadCardsList(const string& anXmlFile);
	static CardData* GetCard(const string aCardName);

private:
	static CardFactory* myInstance;
	std::unordered_map<std::string, CardData> myCardDatas;
	CardFactory();
};

