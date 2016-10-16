#pragma once
#include "CardData.h"
class CardFactory
{
public:
	CardFactory();
	~CardFactory();

	void LoadCards();
	CardData& GetCard();

private:
	std::unordered_map<std::string, CardData> myCardDatas;
};

