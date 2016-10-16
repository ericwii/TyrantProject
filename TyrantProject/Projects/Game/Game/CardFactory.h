#pragma once
#include "CardData.h"
class CardFactory
{
public:
	CardFactory();
	~CardFactory();

	void LoadCards();
	void LoadCardsList(const string& anXmlFile);
	CardData& GetCard(const string aCardName);

private:
	std::unordered_map<std::string, CardData> myCardDatas;
};

