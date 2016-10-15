#pragma once
#include "Surface.h"
#include <unordered_map>

class Effect2D;

class TextFont
{
	friend class Text;
public:
	TextFont();
	~TextFont();

	bool Init(Effect2D* aTextEffect, const string& aTextureFilepath, float aTextureWidth = 512.f, float aTextureHeight = 512.f);

	inline const Vector2<float>& GetCharacterUV(char aCharacter) const;
	inline const Vector2<float>& GetCharacterSize() const;
	inline Effect2D* GetEffect() const;

private:
	Vector2<float> GetCharacterUVFromGrid(int x, int y);

	std::unordered_map<char, Vector2<float>> myCharacters;
	Vector2<float> myCharacterSize;
	Vector2<float> myNormalizedCharacterSize;
	Vector2<float> myTextureSize;
	Surface mySurface;
	Effect2D* myTextEffect;
};


inline const Vector2<float>& TextFont::GetCharacterUV(char aCharacter) const
{
	DEBUG_ASSERT(myCharacters.find(aCharacter) != myCharacters.end(), "Failed to find character to get UV from");
	return myCharacters.at(aCharacter);
}

inline const Vector2<float>& TextFont::GetCharacterSize() const
{
	return myCharacterSize;
}

inline Effect2D* TextFont::GetEffect() const
{
	return myTextEffect;
}