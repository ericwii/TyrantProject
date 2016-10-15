#pragma once
#include <unordered_map>

class Texture;

class TextureContainer
{
public:
	TextureContainer();
	~TextureContainer();

	Texture* GetTexture(const string& aFileName);

private:
	std::unordered_map<std::string, Texture*> myTextures;
};

