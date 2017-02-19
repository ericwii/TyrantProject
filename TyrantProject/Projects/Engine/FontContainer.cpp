#include "stdafx.h"
#include "FontContainer.h"
#include "TextFont.h"

FontContainer::FontContainer()
{
}

FontContainer::~FontContainer()
{
}


TextFont* FontContainer::GetFont(const string& aFontFile, eEffectType anEffectType, Vector2<float> aFontTextureSize)
{
	std::string fontKey = aFontFile.c_str();
	fontKey += std::to_string((int)anEffectType);

	if (myFonts.find(fontKey) == myFonts.end())
	{
		DEBUG_ASSERT(Engine::GetInstance() != nullptr, "Need to start engine before initializing text fonts");
		TextFont* newFont = new TextFont();
		Effect* newEffect = Engine::GetInstance()->GetEffectContainer().GetEffect(anEffectType);

		FontData newData;
		newData.font = newFont;
		newData.effectType = anEffectType;
	
		if (newFont->Init(newEffect, aFontFile, aFontTextureSize.x, aFontTextureSize.y))
		{
			myFonts.insert(std::make_pair(fontKey, newData));
		}
		else
		{
			return nullptr;
		}
	}
	return myFonts.at(fontKey).font;
}