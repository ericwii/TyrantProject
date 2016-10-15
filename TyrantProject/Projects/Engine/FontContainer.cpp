#include "stdafx.h"
#include "FontContainer.h"
#include "TextFont.h"
#include "EffectText.h"

FontContainer::FontContainer()
{
}

FontContainer::~FontContainer()
{
}


TextFont* FontContainer::GetFont(const string& aFontFile, Vector2<float> aFontTextureSize)
{
	if (myFonts.find(aFontFile.c_str()) == myFonts.end())
	{
		DEBUG_ASSERT(Engine::GetInstance() != nullptr, "Need to start engine before initializing text fonts");
		TextFont* newFont = new TextFont();
		Effect2D* newEffect = Engine::GetInstance()->GetEffectContainer().GetEffect(eEffectType2D::Text);
	
		if (newFont->Init(newEffect, aFontFile, aFontTextureSize.x, aFontTextureSize.y))
		{
			myFonts.insert(std::make_pair(aFontFile.c_str(), newFont));
		}
		else
		{
			return nullptr;
		}
	}
	return myFonts.at(aFontFile.c_str());
}