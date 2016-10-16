#pragma once
#include "../../Engine/Text.h"
#include "CardData.h"

class Card
{
public:
	Card();
	~Card();

	void Render();

	void LoadFromXMl(const string& anXmlFile);

	void LoadCard(string aCardName);


private:
	Instance myCanvas;
	CardData* myCardData;
};
