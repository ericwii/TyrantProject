#include "stdafx.h"
#include "Card.h"
#include "XMLReader.h"

using namespace tinyxml2;

Card::Card()
{
}

Card::~Card()
{
}


void Card::LoadFromXMl(const string& anXmlFile)
{
	XMLReader reader;
	reader.OpenDocument(anXmlFile.c_str());
	
	XMLElement* element = reader.FindFirstChild("root");
	element = element->FirstChildElement();
	
	string name = element->Attribute("name");
	string illustration = element->Attribute("illustration");
}