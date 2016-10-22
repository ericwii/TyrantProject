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
}


void Card::LoadCard(string aCardName)
{
	myCardData = CardFactory::GetInstance().GetCard(aCardName);
	DEBUG_ASSERT(myCardData != nullptr, "Failed to get card data from factory");

	LoadModels();
	LoadText();

	myRenderPassIndex = static_cast<unsigned int>(myCardData->faction);
}

void Card::LoadCard(CardData* someData)
{
	myCardData = someData;
	LoadCanvas();
	LoadModels();
	LoadText();

	myRenderPassIndex = static_cast<unsigned int>(myCardData->faction);
}

void Card::SetPosition(const Vector3<float>& aPosition)
{
	myCanvas.SetPosition(aPosition);
}


//Private methods

void Card::LoadModels()
{
	Model* illustrationModel = ModelLoader::LoadRectangle3D(Vector2<float>(1.24f, 1.1f), eEffectType::Textured, myCardData->illustrationPath);
	myIllustration.Init(illustrationModel);
	myIllustration.SetPosition(Vector3<float>(0, 0.235f, 0));
	
	
	
	myCanvas.AddChild(&myIllustration);
}

void Card::LoadText()
{
	FontContainer& container = Engine::GetInstance()->GetFontContainer();
	
	myNameText.Init(container.GetFont("Data/Fonts/DebugFont.dds",eEffectType::Text3D));
	myNameText.SetCharacterSpace(0.8f);
	myNameText.SetText(myCardData->name);
	myNameText.SetPosition(Vector2<float>(-0.55f, 0.88f));
	//myNameText.SetCharacterScale(0.35f);
	
	
	myCanvas.AddChild(&myNameText);
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
	Model* canvasModel = ModelLoader::LoadRectangle3D(Vector2<float>(1.3f, 2.f), eEffectType::Card, canvasPath, true);
	myCanvas.Init(canvasModel);
}