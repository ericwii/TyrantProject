#pragma once
#include "../../Engine/Text3D.h"

class Card
{
public:
	Card();
	~Card();

	void Update(float aDeltaTime);
	void Render();

	void LoadCard(string aCardName);
	void LoadCard(CardData* someData);
	void LowerCooldown();
	void LerpToOrientation(CU::Matrix44<float> aOrientation, float aTime);

	void SetOrientation(const CU::Matrix44<float>& anOrientation);
	void SetPosition(const Vector3<float>& aPosition);

	inline eCardType GetCardType();
	inline CU::Matrix44<float>& GetOrientation();
	inline bool IsLerping();

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

	CU::Matrix44<float> myLerpStart;
	CU::Matrix44<float> myLerpTarget;
	float myCurrentLerpTime;
	float myTargetLerpTime;
	CardData* myCardData;
	unsigned int myRenderPassIndex;
	char myCooldown;
	char myHealth;
	char myAttack;

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

inline CU::Matrix44<float>& Card::GetOrientation()
{
	return myCanvas.GetOrientation();
}

inline bool Card::IsLerping()
{
	return myTargetLerpTime > 0;
}