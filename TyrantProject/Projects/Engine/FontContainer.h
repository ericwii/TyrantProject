#pragma once
#include <unordered_map>

class TextFont;

class FontContainer
{
public:
	FontContainer();
	~FontContainer();

	TextFont* GetFont(const string& aFontFile, eEffectType anEffectType,  Vector2<float> aFontTextureSize = Vector2<float>(512.f,512.f));

private:
	struct FontData
	{
		TextFont* font;
		eEffectType effectType;
	};

	std::unordered_map<std::string, FontData> myFonts;
};

