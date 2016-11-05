#include "stdafx.h"
#include "Card.h"

using namespace tinyxml2;

eCardFaction cardFaction;

Card::Card() : myRenderPassIndex(0)
{
}

Card::~Card()
{
}

void Card::Render()
{
	myCanvas.Render(true, myRenderPassIndex);
	UpdateText();
}


void Card::LoadCard(string aCardName)
{
	myCardData = CardFactory::GetInstance().GetCard(aCardName);
	DEBUG_ASSERT(myCardData != nullptr, "Failed to get card data from factory");

	LoadCanvas();
	LoadModels();
	LoadText();

	myRenderPassIndex = static_cast<unsigned int>(myCardData->faction);
}

void Card::LoadCard(CardData* someData)
{
	myCardData = someData;
	LoadCanvas();
	LoadModels();
	LoadCardTypeIcon();
	LoadText();

	myRenderPassIndex = static_cast<unsigned int>(myCardData->faction);
}

void Card::SetOrientation(const CU::Matrix44<float>& anOrientation)
{
	myCanvas.SetOrientation(anOrientation);
}

void Card::SetPosition(const Vector3<float>& aPosition)
{
	myCanvas.SetPosition(aPosition);
}

void Card::UpdateText()
{
	if (myCardData->cardType != eCardType::Action)
	{
		string healthText;
		healthText += static_cast<int>(myCardData->health);
		myHealthText.SetText(healthText);

	}

	if (myCardData->cardType == eCardType::Assault)
	{
		string attackText;
		attackText += static_cast<int>(myCardData->attack);
		myAttackText.SetText(attackText);
	}

	if (myCardData->cardType == eCardType::Assault || myCardData->cardType == eCardType::Structure)
	{
		string cooldownText;
		cooldownText += static_cast<int>(myCardData->cooldown);
		myCooldownText.SetText(cooldownText);
	}
}


//Private methods

void Card::LoadModels()
{
	Model* illustrationModel = ModelLoader::LoadRectangle(Vector2<float>(1.24f, 1.1f), eEffectType::Textured, myCardData->illustrationPath);
	myIllustration.Init(illustrationModel);
	myIllustration.SetPosition(Vector3<float>(0, 0.235f, 0));	
	
	myCanvas.AddChild(&myIllustration);

	if (myCardData->cardType != eCardType::Action)
	{
		Model* healthIconModel = ModelLoader::LoadRectangle(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, "Data/Textures/Icons/healthIcon.png");
		myHealthIcon.Init(healthIconModel);
		myHealthIcon.SetPosition(Vector3<float>(0.53f, -0.88f, 0));
		myCanvas.AddChild(&myHealthIcon);
	}

	if (myCardData->cardType == eCardType::Assault)
	{
		Model* attackIconModel = ModelLoader::LoadRectangle(Vector2<float>(0.2f, 0.2f), eEffectType::Textured, "Data/Textures/Icons/attackIcon.png");
		myAttackIcon.Init(attackIconModel);
		myAttackIcon.SetPosition(Vector3<float>(-0.53f, -0.88f, 0));
		myCanvas.AddChild(&myAttackIcon);
	}
	if (myCardData->cardType == eCardType::Assault || myCardData->cardType == eCardType::Structure)
	{
		Model* cooldownIconModel = ModelLoader::LoadRectangle(Vector2<float>(0.3f, 0.3f), eEffectType::Textured, "Data/Textures/Icons/cooldownIcon.png");
		myCooldownIcon.Init(cooldownIconModel);
		myCooldownIcon.SetPosition(Vector3<float>(0.48f, 0.82f, 0));
		myCanvas.AddChild(&myCooldownIcon);
	}
}

void Card::LoadText()
{
	FontContainer& container = Engine::GetInstance()->GetFontContainer();
	TextFont* font = container.GetFont("Data/Fonts/DebugFont.dds", eEffectType::Text3D);
	
	myNameText.Init(font);
	myNameText.SetCharacterSpace(0.8f);
	myNameText.SetText(myCardData->name);
	myNameText.SetPosition(Vector2<float>(-0.55f, 0.88f));

	myCanvas.AddChild(&myNameText);


	if (myCardData->cardType != eCardType::Action)
	{
		string healthText;
		healthText += static_cast<int>(myCardData->health);

		myHealthText.Init(font);
		myHealthText.SetTextPositioning(eTextPositioning::eRight);
		myHealthText.SetCharacterSpace(0.8f);
		myHealthText.SetCharacterScale(2.5f);
		myHealthText.SetText(healthText);
		myHealthText.SetPosition(Vector2<float>(0.35f, -0.86f));
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
		myAttackText.SetPosition(Vector2<float>(-0.35f, -0.86f));
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
	Model* canvasModel = ModelLoader::LoadRectangle(Vector2<float>(1.3f, 2.f), eEffectType::Card, canvasPath, true);
	myCanvas.Init(canvasModel);
}

void Card::LoadCardTypeIcon()
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
}