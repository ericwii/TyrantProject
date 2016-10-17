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
	if (myFonts.find(aFontFile.c_str()) == myFonts.end())
	{
		DEBUG_ASSERT(Engine::GetInstance() != nullptr, "Need to start engine before initializing text fonts");
		TextFont* newFont = new TextFont();
		Effect* newEffect = Engine::GetInstance()->GetEffectContainer().GetEffect(anEffectType);

		FontData newData;
		newData.font = newFont;
		newData.effectType = anEffectType;
	
		if (newFont->Init(newEffect, aFontFile, aFontTextureSize.x, aFontTextureSize.y))
		{
			myFonts.insert(std::make_pair(aFontFile.c_str(), newData));
		}
		else
		{
			return nullptr;
		}
	}
	return myFonts.at(aFontFile.c_str()).font;
}