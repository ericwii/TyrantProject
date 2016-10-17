#pragma once
#include "CardData.h"
#include "../../Engine/Text3D.h"

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
	Text3D myNameText;
	Text3D myAttackText;
	Text3D myHealthText;
	Text3D myCooldownText;
	CardData* myCardData;
	unsigned int myRenderPassIndex;

	void LoadModels();
	void LoadText();
};
