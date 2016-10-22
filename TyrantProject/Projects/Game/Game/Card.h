#pragma once
#include "../../Engine/Text3D.h"

class Card
{
public:
	Card();
	~Card();

	void Render();

	void LoadCard(string aCardName);
	void LoadCard(CardData* someData);

	void SetPosition(const Vector3<float>& aPosition);

private:
	Instance myCanvas;
	Instance myIllustration;
	Instance myHealthIcon;
	Instance myAttackIcon;
	Instance myCooldownIcon;
	Instance myCardTypeIcon;
	Text3D myNameText;
	Text3D myAttackText;
	Text3D myHealthText;
	Text3D myCooldownText;
	CardData* myCardData;
	unsigned int myRenderPassIndex;

	void LoadModels();
	void LoadText();
	void LoadCanvas();
	void LoadCardTypeIcon();
};
