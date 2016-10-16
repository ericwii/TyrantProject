#pragma once
#include "../../Engine/Text.h"
#include "CardData.h"

class Card
{
public:
	Card();
	~Card();

	void Render();

	void LoadCard(string aCardName);


private:
	Instance myCanvas;
	Instance myIllustration;
	Text myNameText;
	Text myAttackText;
	Text myHealthText;
	Text myCooldownText;
	CardData* myCardData;
	unsigned int myRenderPassIndex;

	void LoadModels();
	void LoadText();
};
