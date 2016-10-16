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


void Card::LoadCard(string aCardName)
{
	myCardData = CardFactory::GetCard(aCardName);
	DEBUG_ASSERT(myCardData != nullptr, "Failed to get card data from factory");


}



//Private methods

void Card::LoadModels()
{

}

void Card::LoadText()
{

}