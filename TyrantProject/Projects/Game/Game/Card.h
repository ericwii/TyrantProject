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

	void SetOrientation(const CU::Matrix44<float>& anOrientation);
	void SetPosition(const Vector3<float>& aPosition);

	void LowerCooldown();

	inline eCardType GetCardType();

private:
	void UpdateText();


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
	char myCooldown;

	void LoadModels();
	void LoadText();
	void LoadCanvas();
	void LoadCardTypeIcon();
};


inline eCardType Card::GetCardType()
{
	if (myCardData != nullptr)
	{
		return myCardData->cardType;
	}
	else
	{
		return eCardType::Action;
	}
}