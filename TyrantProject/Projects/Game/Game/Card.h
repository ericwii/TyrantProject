#pragma once
#include "../../Engine/Text3D.h"
#include "GUIPopupWindow.h"

struct OnComingAction;
class Player;

enum eStatusEffectType
{
	Protect,
	Augment,
	Enfeeble,
	Poison,
	Stun,
	Jam,
	Immobilize,
	Sunder,
	Disease,
	Phase,
	Chaos,
	Freeze,
};

struct StatusEffect
{
	StatusEffect() : icon(nullptr), effectType(eStatusEffectType (-1)),number(-1), hasIcon(false)
	{

	}

	StatusEffect(eStatusEffectType aType) : effectType(aType), hasIcon(false), number(1)
	{
	}

	StatusEffect(string anIconPath, Model* aBackgroundModel, TextFont* aFont, eStatusEffectType aType, char aNumber)
	{
		icon.Init(ModelLoader::LoadRectangle(Vector2<float>(0.15f, 0.15f), eEffectType::Textured, anIconPath));
		background.Init(aBackgroundModel);
		text.Init(aFont);
		text.SetCharacterScale(Vector2<float>(1.5f, 1.5f));

		effectType = aType;
		number = aNumber;
		UpdateText();

		background.SetAlpha(0.5f);
		icon.SetAlpha(0.5f);
	}

	void UpdateText()
	{
		if (hasIcon)
		{
			string textString;
			textString += number;
			text.SetText(textString);
		}
	}

	Instance background;
	Instance icon;
	Text3D text;
	eStatusEffectType effectType;
	bool hasIcon;
	char number;
};

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
	void Upkeep();
	void CleanUp();

	void OnAttacked(Card* aUser, char& someDamage, Card* anAttacker);
	void OnKill(Card* aCard, Card* akilledCard);
	void OnDamageDealt(Card* aCard, Card* aDamagedCard, char someDamage);
	Card* OnTargeted(AbilityBase* targetingAbility);

	void TakeDamage(char& someDamage);
	void Heal(short someHealth);
	void Weaken(char someWeaken);
	void Rally(char someRally);
	void Berserk(char someAttackIncrese);
	void Cleanse();

	void AddStatusEffect(eStatusEffectType aType, string iconPath = string(), char anAmount = 1);
	void RemoveStatusEffect(eStatusEffectType aStatusEffectType);

	bool CanAttack();
	bool CanUseActivationAbility();
	bool HasNegativeStatusEffect();

	void SetPopupHitbox();
	void SetOrientation(const CU::Matrix44<float>& anOrientation);
	void SetPosition(const Vector3<float>& aPosition);

	inline char GetStatusEffectNumber(eStatusEffectType aStatusEffectType);
	inline GUIPopupWindow& GetPopup();
	inline CU::VectorOnStack<AbilityBase*, 3> GetAbilities();
	inline eCardType GetCardType();
	inline eCardFaction GetFaction();
	inline CU::Matrix44<float>& GetOrientation();
	inline Vector3<float> GetPosition();
	inline Player* GetOwner();
	inline Instance& GetInstance();
	inline bool IsLerping() const;
	inline bool IsDying() const;
	inline bool IsDead() const;
	inline bool IsAtMaxHealth() const;
	inline char GetAttack();
	inline char GetCooldown();
	inline short GetHealth();


private:
	GUIPopupWindow myPopup;
	Instance myCanvas;
	Instance myIllustration;
	Instance myHealthIcon;
	Instance myAttackIcon;
	Instance myCooldownIcon;
	Instance myCardTypeIcon;
	Text3D myAttackText;
	Text3D myHealthText;
	Text3D myCooldownText;

	CU::VectorOnStack<Instance, 3> myAbilityIcons;
	CU::GrowingArray<StatusEffect> myStatusEffects;
	CU::Matrix44<float> myLerpStart;
	CU::Matrix44<float> myLerpTarget;
	Collider::Hitbox2D myPopupHitbox;
	Player* myOwner;
	CardData* myCardData;
	float myCurrentLerpTime;
	float myTargetLerpTime;
	float myCurrentDeathFadeTime;
	unsigned int myRenderPassIndex;
	bool myIsDying;
	bool myIsDead;
	char myCooldown;
	short myHealth;
	char myAttack;
	char myTempAttackChange;
	char myPermanentAttackChange;

	bool myHasBeenStunnedThisTurn;

	void PositionStatusEffectIcons();
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

inline GUIPopupWindow& Card::GetPopup()
{
	return myPopup;
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

inline Instance& Card::GetInstance()
{
	return myCanvas;
}

inline Vector3<float> Card::GetPosition()
{
	return myCanvas.GetPosition();
}

inline char Card::GetStatusEffectNumber(eStatusEffectType aStatusEffectType)
{
	for (int i = 0; i < myStatusEffects.Size(); ++i)
	{
		if (myStatusEffects[i].effectType == aStatusEffectType)
		{
			return myStatusEffects[i].number;
		}
	}
	return 0;
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

inline short Card::GetHealth()
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
