#include "stdafx.h"
#include "Card.h"
#include "CardGameTextManager.h"
#include "AbilityBase.h"

Vector4<float> damagedHealthColor(1.f, 0, 0, 1.f);
Vector4<float> ralliedAttackColor(0, 1.f, 0, 1.f);
Vector4<float> weakenedAttackColor(1.f, 0, 0, 1.f);

TextFont* textFont;
string currentStatusEffectText;
Model* statusEffectIconBackgrund;
Vector2<float> statusEffectIconOffset(-0.6f, 0.85f);
float statusEffectIconSpacing = 0.2f;


using namespace tinyxml2;

float deathFadeTime = 0.8f;

Card::Card() : myRenderPassIndex(0), myTargetLerpTime(-1.f), myIsDying(false), myIsDead(false), myHasBeenStunnedThisTurn(false),
	myOwner(nullptr), myTempAttackChange(0), myPermanentAttackChange(0)
{
}

Card::Card(Player* anOwner) : myRenderPassIndex(0), myTargetLerpTime(-1.f), myIsDying(false), myIsDead(false), myHasBeenStunnedThisTurn(false),
	myOwner(anOwner), myTempAttackChange(0), myPermanentAttackChange(0)
{
}

Card::~Card()
{
}

void Card::Update(float aDeltaTime)
{
	if (myTargetLerpTime > 0)
	{
		myCurrentLerpTime += aDeltaTime;
		float lerp = MIN(myCurrentLerpTime / myTargetLerpTime, 1.f);

		CU::Matrix44<float> orientation;
		for (int i = 0; i < 15; ++i)
		{
			orientation.matrix[i] = LERP(myLerpStart.matrix[i], myLerpTarget.matrix[i], lerp);
		}

		Vector3<float> position = orientation.GetPosition();
		orientation.SetPosition(Vector3<float>(0, 0, 0));
		myCanvas.SetOrientation(orientation);
		myCanvas.SetPosition(position);

		if (myCurrentLerpTime >= myTargetLerpTime)
		{
			myTargetLerpTime = -1.f;
			myCurrentLerpTime = 0;
		}
	}

	if (myIsDead == false && myIsDying == true)
	{
		myCurrentDeathFadeTime += aDeltaTime;

		float alpha = 1 - myCurrentDeathFadeTime / deathFadeTime;
		if (myCurrentDeathFadeTime >= deathFadeTime)
		{
			alpha = 0;
			myIsDead = true;
		}

		myCanvas.SetAlpha(alpha);		
	}
}

void Card::Render()
{
	myCanvas.Render(true, myRenderPassIndex);
}


void Card::LoadCard(string aCardName)
{
	myCardData = CardFactory::GetInstance().GetCard(aCardName);
	DEBUG_ASSERT(myCardData != nullptr, "Failed to get card data from factory");

	LoadCanvas();
	LoadModels();
	LoadText();
	LoadIcons();

	myRenderPassIndex = 0;
	myStatusEffects.Allocate(4);
	myCooldown = myCardData->cooldown;
	myAttack = myCardData->attack;
	myHealth = myCardData->health;

	if (statusEffectIconBackgrund == nullptr)
	{
		textFont = Engine::GetInstance()->GetFontContainer().GetFont("Data/Fonts/debugFont.dds", eEffectType::Text3D);
		statusEffectIconBackgrund = ModelLoader::LoadRectangle(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, "Data/Textures/Icons/statusEffectBackground.png");
	}
}

void Card::LoadCard(CardData* someData)
{
	myCardData = someData;
	LoadCanvas();
	LoadModels();
	LoadIcons();
	LoadText();

	myRenderPassIndex = 0;
	myStatusEffects.Allocate(4);
	myCooldown = myCardData->cooldown;
	myAttack = myCardData->attack;
	myHealth = myCardData->health;

	if (statusEffectIconBackgrund == nullptr)
	{
		textFont = Engine::GetInstance()->GetFontContainer().GetFont("Data/Fonts/debugFont.dds", eEffectType::Text3D);
		statusEffectIconBackgrund = ModelLoader::LoadRectangle(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, "Data/Textures/Icons/statusEffectBackground.png");
	}
}

void Card::LerpToOrientation(CU::Matrix44<float> aOrientation, float aTime)
{
	myLerpStart = myCanvas.GetOrientation();
	myLerpTarget = aOrientation;
	myTargetLerpTime = aTime;
	myCurrentLerpTime = 0;
}

void Card::LowerCooldown()
{
	if (myCooldown > 0 && GetStatusEffectNumber(eStatusEffectType::Freeze) < 1)
	{
		--myCooldown;

		string newCooldown;
		newCooldown += myCooldown;
		myCooldownText.SetText(newCooldown);

		if (myCooldown < 1)
		{
			myCanvas.RemoveChild(&myCooldownIcon);
			myCanvas.RemoveChild(&myCooldownText);
		}
	}
}

void Card::Upkeep()
{
	RemoveStatusEffect(eStatusEffectType::Protect);
	RemoveStatusEffect(eStatusEffectType::Enfeeble);

	char poison = GetStatusEffectNumber(eStatusEffectType::Poison);
	TakeDamage(poison);

	if (!myIsDying)
	{
		LowerCooldown();
	}
}

void Card::CleanUp()
{
	if (myCardData != nullptr && myCardData->cardType == eCardType::Assault)
	{
		if (myHasBeenStunnedThisTurn == false)
		{
			RemoveStatusEffect(eStatusEffectType::Stun);
		}
		myHasBeenStunnedThisTurn = false;

		RemoveStatusEffect(eStatusEffectType::Augment);
		RemoveStatusEffect(eStatusEffectType::Chaos);
		RemoveStatusEffect(eStatusEffectType::Immobilize);
		RemoveStatusEffect(eStatusEffectType::Jam);
		RemoveStatusEffect(eStatusEffectType::Phase);

		myTempAttackChange = 0;
		string attack;
		attack += myAttack;
		myAttackText.SetText(attack);

		if (myAttack > myCardData->attack)
		{
			myAttackText.SetColor(ralliedAttackColor);
		}
		else
		{
			myAttackText.SetColor(Vector4<float>(1.f, 1.f, 1.f, 1.f));
		}
	}
}

void Card::TakeDamage(char& someDamage)
{
	someDamage += GetStatusEffectNumber(eStatusEffectType::Enfeeble);

	someDamage -= GetStatusEffectNumber(eStatusEffectType::Protect);
	if (someDamage < 0)
	{
		someDamage = 0;
	}



	if (someDamage > 0)
	{
		CardGameTextManager::AddDamageText(someDamage, myCanvas.GetPosition());

		myHealth -= someDamage;
		if (myHealth <= 0)
		{
			myHealth = 0;
			for (char j = 0; j < myCardData->abilities.Size(); j++)
			{
				myCardData->abilities[j]->OnDeath(this);
			}
		}

		if (myHealth <= 0)
		{
			myIsDying = true;
			myCurrentDeathFadeTime = 0;
		}

		string health;
		health += myHealth;
		myHealthText.SetText(health);

		if (someDamage > 0)
		{
			myHealthText.SetColor(damagedHealthColor);
		}
	}
}

void Card::Heal(char someHealth)
{
	if (myCardData != nullptr && myHealth < myCardData->health && GetStatusEffectNumber(eStatusEffectType::Disease) < 1)
	{
		if (myHealth + someHealth <= myCardData->health)
		{
			CardGameTextManager::AddHealingText(someHealth, myCanvas.GetPosition());
			myHealth += someHealth;
		}
		else
		{
			CardGameTextManager::AddHealingText(myCardData->health - myHealth, myCanvas.GetPosition());
			myHealth = myCardData->health;
		}

		string health;
		health += myHealth;
		myHealthText.SetText(health);

		if (myHealth == myCardData->health)
		{
			myHealthText.SetColor(Vector4<float>(1.f, 1.f, 1.f, 1.f));
		}
	}
}

void Card::Weaken(char someWeaken)
{
	myTempAttackChange -= someWeaken;


	string attack;
	if (myAttack + myTempAttackChange < 0)
	{
		attack += "-";
		attack += ABS(myAttack + myTempAttackChange);
	}
	else
	{
		attack += (myAttack + myTempAttackChange);
	}
	myAttackText.SetText(attack);

	if (myTempAttackChange < 0)
	{
		myAttackText.SetColor(weakenedAttackColor);
	}
	else if (myTempAttackChange > 0)
	{
		myAttackText.SetColor(ralliedAttackColor);	
	}
	else
	{
		myAttackText.SetColor(Vector4<float>(1.f, 1.f, 1.f, 1.f));
	}
}

void Card::Rally(char someRally)
{
	if (GetStatusEffectNumber(eStatusEffectType::Sunder) < 1)
	{
		myTempAttackChange += someRally;

		string attack;

		if (myAttack + myTempAttackChange < 0)
		{
			attack += "-";
			attack += ABS(myAttack + myTempAttackChange);
		}
		else
		{
			attack += (myAttack + myTempAttackChange);
		}
		myAttackText.SetText(attack);

		if (myTempAttackChange > 0)
		{
			myAttackText.SetColor(ralliedAttackColor);
		}
		else if (myTempAttackChange < 0)
		{
			myAttackText.SetColor(weakenedAttackColor);
		}
		else
		{
			myAttackText.SetColor(Vector4<float>(1.f, 1.f, 1.f, 1.f));
		}
	}
}

void Card::Berserk(char someAttackIncrese)
{
	if (GetStatusEffectNumber(eStatusEffectType::Sunder) < 1)
	{
		myAttack += someAttackIncrese;

		string attack;

		if (myAttack < 0)
		{
			attack += "-";
			attack += ABS(myAttack + myTempAttackChange);
		}
		else
		{
			attack += (myAttack + myTempAttackChange);
		}
		myAttackText.SetText(attack);

		if (myAttack > myCardData->attack)
		{
			myAttackText.SetColor(ralliedAttackColor);
		}
		else if (myAttack < myCardData->attack)
		{
			myAttackText.SetColor(weakenedAttackColor);
		}
		else
		{
			myAttackText.SetColor(Vector4<float>(1.f, 1.f, 1.f, 1.f));
		}
	}
}

void Card::Cleanse()
{
	if (GetStatusEffectNumber(eStatusEffectType::Phase) == 0)
	{
		eStatusEffectType currentStatusEffect;
		for (int i = 0; i < myStatusEffects.Size(); ++i)
		{
			currentStatusEffect = myStatusEffects[i].effectType;
			if (currentStatusEffect != eStatusEffectType::Augment && currentStatusEffect != eStatusEffectType::Protect)
			{
				myStatusEffects.RemoveCyclicAtIndex(i);
			}
		}
	}

	myHasBeenStunnedThisTurn = false;
}

void Card::AddStatusEffect(eStatusEffectType aType, string iconPath, char anAmount)
{
	for (int i = 0; i < myStatusEffects.Size(); ++i)
	{
		if (myStatusEffects[i].effectType == aType)
		{
			myStatusEffects[i].number += anAmount;	
			myStatusEffects[i].UpdateText();
			return;
		}
	}


	if (iconPath.Lenght() > 0)
	{
		myStatusEffects.Add(StatusEffect(iconPath, statusEffectIconBackgrund, textFont, aType, anAmount));
		StatusEffect& newStatus = myStatusEffects.GetLast();

		myCanvas.AddChild(&newStatus.background);
		myCanvas.AddChild(&newStatus.icon);
		myCanvas.AddChild(&newStatus.text);
	}
	else
	{
		myStatusEffects.Add(StatusEffect(aType));
		if (aType == eStatusEffectType::Stun)
		{
			myHasBeenStunnedThisTurn = true;
		}
	}

	PositionStatusEffectIcons();
}

void Card::RemoveStatusEffect(eStatusEffectType aStatusEffectType)
{
	for (int i = 0; i < myStatusEffects.Size(); ++i)
	{
		if (myStatusEffects[i].effectType == aStatusEffectType)
		{
			if (myStatusEffects[i].hasIcon)
			{
				myCanvas.RemoveChild(&myStatusEffects[i].background);
				myCanvas.RemoveChild(&myStatusEffects[i].icon);
				myCanvas.RemoveChild(&myStatusEffects[i].text);
			}

			if (myStatusEffects.Size() > 1 && i < myStatusEffects.Size() - 1)
			{
				StatusEffect& lastStatus = myStatusEffects.GetLast();
				if (lastStatus.hasIcon)
				{
					myCanvas.RemoveChild(&lastStatus.background);
					myCanvas.RemoveChild(&lastStatus.icon);
					myCanvas.RemoveChild(&lastStatus.text);
				}

				myStatusEffects.RemoveCyclicAtIndex(i);

				if (myStatusEffects[i].hasIcon)
				{
					myCanvas.AddChild(&myStatusEffects[i].background);
					myCanvas.AddChild(&myStatusEffects[i].icon);
					myCanvas.AddChild(&myStatusEffects[i].text);
				}

				PositionStatusEffectIcons();
			}
			else
			{
				myStatusEffects.RemoveCyclicAtIndex(i);
			}
		}
	}
}

void Card::OnAttacked(Card* aUser, char& someDamage, Card* anAttacker)
{
	for (int i = 0; i < myCardData->abilities.Size(); ++i)
	{
		myCardData->abilities[i]->OnAttacked(aUser,someDamage, anAttacker);
		if (someDamage > 0)
		{
			myCardData->abilities[i]->OnCombatDamaged(someDamage, this, anAttacker);
		}
	}


}

void Card::OnKill(Card* aCard, Card* akilledCard)
{
	for (int i = 0; i < myCardData->abilities.Size(); ++i)
	{
		myCardData->abilities[i]->OnKill(aCard, akilledCard);
	}
}

void Card::OnDamageDealt(Card * aCard, Card * aDamagedCard, char someDamage)
{
	for (int i = 0; i < myCardData->abilities.Size(); ++i)
	{
		myCardData->abilities[i]->OnDamageDealt(aCard, aDamagedCard, someDamage);
	}
}

Card* Card::OnTargeted(AbilityBase* targetingAbility)
{
	Card* target = this;
	for (int i = 0; i < myCardData->abilities.Size(); ++i)
	{
		if (target == this)
		{
			myCardData->abilities[i]->OnTargeted(target, targetingAbility);
		}
	}

	return target;
}

bool Card::CanAttack()
{
	bool canAttack = true;
	eStatusEffectType currentEffectType;
	for (int i = 0; i < myStatusEffects.Size(); ++i)
	{
		currentEffectType = myStatusEffects[i].effectType;
		if (currentEffectType == eStatusEffectType::Jam || currentEffectType == eStatusEffectType::Immobilize || 
			currentEffectType == eStatusEffectType::Freeze || currentEffectType == eStatusEffectType::Stun)
		{
			canAttack = false;
			break;
		}
	}

	return canAttack && !myIsDying && myAttack + myTempAttackChange > 0;
}

bool Card::CanUseActivationAbility()
{
	return GetStatusEffectNumber(eStatusEffectType::Jam) < 1 && GetStatusEffectNumber(eStatusEffectType::Freeze) < 1;
}


void Card::SetOrientation(const CU::Matrix44<float>& anOrientation)
{
	myCanvas.SetOrientation(anOrientation);
}

void Card::SetPosition(const Vector3<float>& aPosition)
{
	myCanvas.SetPosition(aPosition);
}




//Private methods

void Card::PositionStatusEffectIcons()
{
	Vector2<float> currentPosition = statusEffectIconOffset;
	Vector2<float> textOffset(-0.07f,0.05f);
	for (int i = 0; i < myStatusEffects.Size(); ++i)
	{
		if (myStatusEffects[i].hasIcon)
		{
			myCanvas.SetChildPosition(&myStatusEffects[i].background, currentPosition);
			myCanvas.SetChildPosition(&myStatusEffects[i].icon, currentPosition);
			myCanvas.SetChildPosition(&myStatusEffects[i].text, currentPosition + textOffset);
			myStatusEffects[i].UpdateText();
			currentPosition.x += statusEffectIconSpacing;
		}
	}
}

void Card::LoadModels()
{
	Model* illustrationModel = ModelLoader::LoadRectangle(Vector2<float>(1.4f, 1.1f), eEffectType::Textured, myCardData->illustrationPath);
	myIllustration.Init(illustrationModel);
	myIllustration.SetPosition(Vector3<float>(0, 0.235f, 0));
	
	myCanvas.AddChild(&myIllustration);

	if (myCardData->cardType != eCardType::Action)
	{
		Model* healthIconModel = ModelLoader::LoadRectangle(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, "Data/Textures/Icons/healthIcon.png");
		myHealthIcon.Init(healthIconModel);
		myHealthIcon.SetPosition(Vector3<float>(0.6f, -0.88f, 0));
		myCanvas.AddChild(&myHealthIcon);
	}

	if (myCardData->cardType == eCardType::Assault)
	{
		Model* attackIconModel = ModelLoader::LoadRectangle(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, "Data/Textures/Icons/attackIcon.png");
		myAttackIcon.Init(attackIconModel);
		myAttackIcon.SetPosition(Vector3<float>(-0.6f, -0.88f, 0));
		myCanvas.AddChild(&myAttackIcon);
	}
	if (myCardData->cardType == eCardType::Assault || myCardData->cardType == eCardType::Structure)
	{
		Model* cooldownIconModel = ModelLoader::LoadRectangle(Vector2<float>(0.45f, 0.3f), eEffectType::Textured, "Data/Textures/Icons/cooldownIcon.png");
		myCooldownIcon.Init(cooldownIconModel);
		myCooldownIcon.SetPosition(Vector3<float>(0.48f, 0.82f, 0));
		myCanvas.AddChild(&myCooldownIcon);
	}
}

void Card::LoadText()
{
	FontContainer& container = Engine::GetInstance()->GetFontContainer();
	TextFont* font = container.GetFont("Data/Fonts/debugFont.dds", eEffectType::Text3D);
	
	myNameText.Init(font);
	myNameText.SetCharacterSpace(0.8f);
	myNameText.SetText(myCardData->name);
	myNameText.SetPosition(Vector2<float>(-0.55f, 0.88f));
	myNameText.SetCurrentOrientationAsOriginal();

	//myCanvas.AddChild(&myNameText);


	if (myCardData->cardType != eCardType::Action)
	{
		string healthText;
		healthText += static_cast<int>(myCardData->health);

		myHealthText.Init(font);
		myHealthText.SetTextPositioning(eTextPositioning::eRight);
		myHealthText.SetCharacterSpace(0.8f);
		myHealthText.SetCharacterScale(2.5f);
		myHealthText.SetText(healthText);
		myHealthText.SetPosition(Vector2<float>(0.4f, -0.86f));
		myHealthText.SetCurrentOrientationAsOriginal();
		myCanvas.AddChild(&myHealthText);
	}

	if (myCardData->cardType == eCardType::Assault)
	{
		string attackText;
		attackText += static_cast<int>(myCardData->attack);

		myAttackText.Init(font);
		myAttackText.SetCharacterSpace(0.8f);
		myAttackText.SetCharacterScale(2.5f);
		myAttackText.SetText(attackText);
		myAttackText.SetPosition(Vector2<float>(-0.4f, -0.86f));
		myAttackText.SetCurrentOrientationAsOriginal();
		myCanvas.AddChild(&myAttackText);
	}
	
	if (myCardData->cardType == eCardType::Assault || myCardData->cardType == eCardType::Structure)
	{
		string cooldownText;
		cooldownText += static_cast<int>(myCardData->cooldown);

		myCooldownText.Init(font);
		myCooldownText.SetCharacterSpace(0.8f);
		myCooldownText.SetCharacterScale(2.5f);
		myCooldownText.SetText(cooldownText);
		myCooldownText.SetPosition(Vector2<float>(0.48f, 0.84f));
		myCooldownText.SetCurrentOrientationAsOriginal();
		myCanvas.AddChild(&myCooldownText);
	}
}

void Card::LoadCanvas()
{
	string canvasPath;
	switch (myCardData->faction)
	{
		case(eCardFaction::BloodThirsty) :
		{
			canvasPath = "Data/Textures/CardCanvas/BloodThirstyCanvas.png";
			break;
		}
		case(eCardFaction::Imperial) :
		{
			canvasPath = "Data/Textures/CardCanvas/ImperialCanvas.png";
			break;
		}
		case(eCardFaction::Raider) :
		{
			canvasPath = "Data/Textures/CardCanvas/RaiderCanvas.png";
			break;
		}
		case(eCardFaction::Righteous) :
		{
			canvasPath = "Data/Textures/CardCanvas/RighteousCanvas.png";
			break;
		}
		case(eCardFaction::Xeno) :
		{
			canvasPath = "Data/Textures/CardCanvas/XenoCanvas.png";
			break;
		}
		default: //Action
		{
			canvasPath = "Data/Textures/CardCanvas/canvas.png";
			break;
		}
	}
	Model* canvasModel = ModelLoader::LoadRectangle(Vector2<float>(1.5f, 2.f), eEffectType::Card, canvasPath, true);
	myCanvas.Init(canvasModel);
}

void Card::LoadIcons()
{
	//Model* cardTypeIcon = nullptr;
	//
	//switch (myCardData->cardType)
	//{
	//	case(eCardType::Action):
	//	{
	//		cardTypeIcon = ModelLoader::LoadRectangle3D(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, "Data/Textures/Icons/actionIcon.png");
	//		break;
	//	}
	//	case(eCardType::Assault):
	//	{
	//		cardTypeIcon = ModelLoader::LoadRectangle3D(Vector2<float>(0.15f, 0.15f), eEffectType::Textured, "Data/Textures/Icons/assaultIcon.png");
	//		break;
	//	}
	//	case(eCardType::Commander):
	//	{
	//		cardTypeIcon = ModelLoader::LoadRectangle3D(Vector2<float>(0.1f, 0.15f), eEffectType::Textured, "Data/Textures/Icons/commanderIcon.png");
	//		break;
	//	}
	//	case(eCardType::Structure):
	//	{
	//		cardTypeIcon = ModelLoader::LoadRectangle3D(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, "Data/Textures/Icons/structureIcon.png");
	//		break;
	//	}
	//	default:
	//	{
	//		break;
	//	}
	//}
	//
	//myCardTypeIcon.Init(cardTypeIcon);
	//myCardTypeIcon.SetPosition(Vector3<float>(-0.53f, 0.87f, 0));
	//
	//myCanvas.AddChild(&myCardTypeIcon);




	float iconSpacing = 0.2f;
	Model* iconModel;
	Instance iconInstance;
	for (int i = 0; i < myCardData->abilities.Size(); ++i)
	{
		iconModel = ModelLoader::LoadRectangle(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, myCardData->abilities[i]->iconTexturePath);
		iconInstance.Init(iconModel);
		iconInstance.SetPosition(Vector3<float>(-0.5f + iconSpacing * i, -0.5f, 0));
		
		myAbilityIcons.Add(iconInstance);
		myCanvas.AddChild(&myAbilityIcons[i]);
	}
}