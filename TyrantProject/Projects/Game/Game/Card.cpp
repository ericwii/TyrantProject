#include "stdafx.h"
#include "Card.h"
#include "XMLReader.h"
#include "CardData.h"
#include "../../Engine/ModelLoader.h"
#include "CardFactory.h"

using namespace tinyxml2;

eCardFaction cardFaction;

Card::Card() : myCardData(nullptr), myRenderPassIndex(0)
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



//Private methods

void Card::LoadModels()
{
	Model* canvasModel = ModelLoader::LoadRectangle3D(Vector2<float>(1.3f, 2.f), eEffectType3D::Card, "Data/Textures/CardCanvas/canvas.png", true);
	canvasModel->AddTexture("HighlightTexture", "Data/Textures/CardCanvas/highlight.png");
	myCanvas.Init(canvasModel);

	Model* illustrationModel = ModelLoader::LoadRectangle3D(Vector2<float>(1.24f, 1.1f), eEffectType3D::Textured, myCardData->illustrationPath);
	myIllustration.Init(illustrationModel);
	myIllustration.SetPosition(Vector3<float>(0, 0.23f, 0));



	myCanvas.AddChild(&myIllustration);
}

void Card::LoadText()
{
	FontContainer& container = Engine::GetInstance()->GetFontContainer();

	myNameText.Init(container.GetFont("Data/Fonts/DebugFont.dds"));
	myNameText.SetText(myCardData->name);
	myNameText.SetPosition(Vector2<float>(-0.1f, -0.22f));
	myNameText.SetCharacterScale(0.35f);
	myNameText.SetCharacterSpace(0.47f);


	myCanvas.AddChild(&myNameText);
}