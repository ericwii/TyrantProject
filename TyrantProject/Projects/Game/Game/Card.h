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
	void LerpToOrientation(CU::Matrix44<float> aOrientation, float aTime);
	void LowerCooldown();
	void TakeDamage(char someDamage);

	void SetOrientation(const CU::Matrix44<float>& anOrientation);
	void SetPosition(const Vector3<float>& aPosition);

	inline eCardType GetCardType();
	inline CU::Matrix44<float>& GetOrientation();
	inline Vector2<float> GetPosition();
	inline bool IsLerping() const;
	inline bool IsDying() const;
	inline bool IsDead() const;

	inline char GetAttack();
	inline char GetCooldown();
	inline char GetHealth();

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
	float myCurrentDeathFadeTime;
	CardData* myCardData;
	unsigned int myRenderPassIndex;
	bool myIsDying;
	bool myIsDead;
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

inline Vector2<float> Card::GetPosition()
{
	return myCanvas.GetPosition();
}

inline bool Card::IsLerping() const
{
	return myTargetLerpTime > 0;
}

inline char Card::GetAttack()
{
	return myAttack;
}

inline char Card::GetCooldown()
{
	return myCooldown;
}

inline char Card::GetHealth()
{
	return myHealth;
}

inline bool Card::IsDying() const
{
	return myIsDying;
}

inline bool Card::IsDead() const
{
	return myIsDead;
}