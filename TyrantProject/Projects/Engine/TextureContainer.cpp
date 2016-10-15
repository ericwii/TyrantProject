#include "stdafx.h"
#include "TextureContainer.h"
#include "Texture.h"

string defaultTexturePath = "Data/Textures/defaultTexture.png";

TextureContainer::TextureContainer()
{
}

TextureContainer::~TextureContainer()
{
}

Texture* TextureContainer::GetTexture(const string& aFileName)
{
	if (myTextures.find(aFileName.c_str()) == myTextures.end())
	{
		Texture* newTexture = new Texture();
		if (newTexture->LoadTexture(aFileName.c_str()))
		{
			myTextures.insert(std::make_pair(aFileName.c_str(), newTexture));
		}
		else
		{
			delete newTexture;
			if (aFileName == defaultTexturePath)
			{
				return nullptr;
			}
			else
			{
				return GetTexture(defaultTexturePath);
			}
		}
	}
	return myTextures.at(aFileName.c_str());
}