#pragma once
#include "../../Engine/Text3D.h"

struct OnComingAction;
class Player;

class Card
{
public:
	Card();
	Card(Player* anOwner);
	~Card();

	void Update(float aDeltaTime);
	void Render();

	void LoadCard(string aCardName);
	void LoadCard(CardData* someData);
	void LerpToOrientation(CU::Matrix44<float> aOrientation, float aTime);
	void LowerCooldown();
	void CleanUp();

	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker);
	void OnKill(Card* aCard, Card* akilledCard);
	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage);
	Card* OnTargeted();

	void TakeDamage(char someDamage);
	void Heal(char someHealth);
	void Weaken(char someWeaken);
	void Rally(char someRally);
	void Berserk(char someAttackIncrese);

	bool CanAttack();

	void SetOrientation(const CU::Matrix44<float>& anOrientation);
	void SetPosition(const Vector3<float>& aPosition);

	inline CU::VectorOnStack<AbilityBase*, 3> GetAbilities();
	inline eCardType GetCardType();
	inline eCardFaction GetFaction();
	inline CU::Matrix44<float>& GetOrientation();
	inline Vector3<float> GetPosition();
	inline Player* GetOwner();
	inline bool IsLerping() const;
	inline bool IsDying() const;
	inline bool IsDead() const;
	inline bool IsAtMaxHealth() const;
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
	CU::VectorOnStack<Instance, 3> myAbilityIcons;
	float myCurrentLerpTime;
	float myTargetLerpTime;
	float myCurrentDeathFadeTime;
	Player* myOwner;
	CardData* myCardData;
	unsigned int myRenderPassIndex;
	bool myIsDying;
	bool myIsDead;
	char myCooldown;
	char myHealth;
	char myAttack;
	char myTempAttackChange;
	char myPermanentAttackChange;

	void LoadModels();
	void LoadText();
	void LoadCanvas();
	void LoadIcons();
};

inline CU::VectorOnStack<AbilityBase*, 3> Card::GetAbilities()
{
	if (myCardData != nullptr)
	{
		return myCardData->abilities;
	}
	else
	{
		return CU::VectorOnStack<AbilityBase*, 3>();
	}
}

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

inline eCardFaction Card::GetFaction()
{
	if (myCardData != nullptr)
	{
		return myCardData->faction;
	}
	else
	{
		return eCardFaction::Action;
	}
}

inline CU::Matrix44<float>& Card::GetOrientation()
{
	return myCanvas.GetOrientation();
}

inline Player* Card::GetOwner()
{
	return myOwner;
}

inline Vector3<float> Card::GetPosition()
{
	return myCanvas.GetPosition();
}

inline bool Card::IsLerping() const
{
	return myTargetLerpTime > 0;
}

inline char Card::GetAttack()
{
	return myAttack + myTempAttackChange + myPermanentAttackChange;
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

inline bool Card::IsAtMaxHealth() const
{
	return myCardData != nullptr && myHealth == myCardData->health;
}
