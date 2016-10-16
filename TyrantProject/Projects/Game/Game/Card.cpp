#include "stdafx.h"
#include "Card.h"
#include "XMLReader.h"
#include "CardData.h"
#include "../../Engine/ModelLoader.h"
#include "CardFactory.h"

using namespace tinyxml2;

eCardFaction cardFaction;

Card::Card()
{
}

Card::~Card()
{
}

void Card::Render()
{
	unsigned int passIndex = cardFaction;
	myCanvas.Render(passIndex);
}


void Card::LoadFromXMl(const string& anXmlFile)
{
	Model* canvasModel = ModelLoader::LoadRectangle3D(Vector2<float>(1.f, 2.f), eEffectType3D::Card, "Data/Textures/CardCanvas/canvas.png", true);
	canvasModel->AddTexture("HighlightTexture", "Data/Textures/CardCanvas/highlight.png");
	myCanvas.Init(canvasModel);

	XMLReader reader;
	reader.OpenDocument(anXmlFile.c_str());

	XMLElement* element = reader.FindFirstChild("root");
	element = element->FirstChildElement();
	
	CardData card;

	card.name = element->Attribute("name");
	string faction = element->Attribute("faction");
	string cardType = element->Attribute("cardType");
	string rarity = element->Attribute("rarity");


	if (faction == "Bloodthirsty")
	{
		card.faction = eCardFaction::BloodThirsty;
	}
	else if (faction == "raider")
	{
		card.faction = eCardFaction::Raider;
	}
	else if (faction == "Righteous")
	{
		card.faction = eCardFaction::Righteous;
	}
	else if (faction == "Xeno")
	{
		card.faction = eCardFaction::Xeno;
	}
	else
	{
		card.faction = eCardFaction::Imperial;
	}

	if (cardType == "Assult")
	{
		card.cardType = eCardType::Assult;
	}
	if (cardType == "Structure")
	{
		card.cardType = eCardType::Structure;
	}
	if (cardType == "Action")
	{
		card.cardType = eCardType::Action;
	}
	else
	{
		card.cardType = eCardType::Commander;
	}

	if (rarity == "Rare")
	{
		card.rarity = eRarity::Rare;
	}
	if (rarity == "Legendary")
	{
		card.rarity = eRarity::Legendary;
	}
	if (rarity == "Uncommon")
	{
		card.rarity = eRarity::Uncommon;
	}
	else
	{
		card.rarity = eRarity::Common;
	}

	card.unique = element->BoolAttribute("unique");
	card.cooldown = static_cast<char>(element->IntAttribute("cooldown"));
	card.attack = static_cast<char>(element->IntAttribute("attack"));
	card.health = static_cast<char>(element->IntAttribute("health"));

	cardFaction = card.faction;
}

void Card::LoadCard(string aCardName)
{
	myCardData = CardFactory::GetInstance().GetCard(aCardName);
}
